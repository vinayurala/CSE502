#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "memory.h"

uint64_t entry;

uint64_t load_elf(char* mem, const char* filename) {
	int fd = open(filename,O_RDONLY);
	Elf64_Ehdr ehdr;
	assert(read(fd,(void*)&ehdr,sizeof(ehdr))==sizeof(ehdr));
	Elf64_Phdr phdr[10];
	int phnum = ehdr.e_phnum;
	assert(phnum < (sizeof(phdr)/sizeof(Elf64_Phdr)));
	assert(lseek(fd,ehdr.e_phoff,SEEK_SET)!=-1);
	assert(read(fd,(void*)&phdr,sizeof(phdr))==sizeof(phdr));
	for(int header=0; header<phnum ; ++header) {
		Elf64_Phdr *p = &phdr[header];
		if (p->p_type == PT_LOAD) {
			if ((p->p_vaddr + p->p_memsz) > mem_size) {
				cerr << "Not enough 'physical' ram" << endl;
				exit(-1);
			}
			memset(mem+p->p_vaddr,0,p->p_memsz);
			assert(lseek(fd,p->p_offset,SEEK_SET)!=-1);
			assert(read(fd,(void*)(mem+p->p_vaddr),p->p_filesz)==p->p_filesz);
			//cerr << "section flags " << hex << p->p_flags << endl;
		} else if (p->p_type == PT_GNU_STACK) {
			// do nothing
		} else {
			cerr << "Unexpected ELF header " << p->p_type << endl;
			exit(-1);
		}
	}
	close(fd);
	return ehdr.e_entry;
}

template<int i_ports, int d_ports>
void Memory<i_ports,d_ports>::mem_init(const char* filename) {
	mem = (char*)mmap(
			(void*)mem_base
		,	mem_size
		,	PROT_READ|PROT_WRITE
		,	MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED|MAP_NORESERVE
		,	0
		,	0
		);
	assert(mem == (void*)mem_base);
	entry = load_elf(mem, filename);
	sc_data dl; assert(dl.length() % 8 == 0);
}

template<int i_ports, int d_ports>
sc_inst Memory<i_ports,d_ports>::mem_i_read(const sc_addr& addr) {
	sc_inst v;
	//assert(addr % (v.length() / 8) == 0); FIXME: should be here, but breaks sample solution; in fact, should just drop lower bits from the addr input to Memory (maybe create a sc_word_addr in const.h for this purpose).
	const int bytecount = v.length()/8;
	for(int bytes = 0; bytes < bytecount; ++bytes)
		v.range((bytecount-bytes)*8-1, (bytecount-bytes-1)*8) = sc_uint<8>(int(mem[addr+bytes]));
	return v;
}

template<int i_ports, int d_ports>
sc_data Memory<i_ports,d_ports>::mem_d_read(const sc_addr& addr) {
	sc_data v;
	//assert(addr % (v.length() / 8) == 0); FIXME: should be here, but breaks sample solution; in fact, should just drop lower bits from the addr input to Memory (maybe create a sc_word_addr in const.h for this purpose).
	const int bytecount = v.length()/8;
	for(int bytes = 0; bytes < bytecount; ++bytes)
		v.range((bytecount-bytes)*8-1, (bytecount-bytes-1)*8) = sc_uint<8>(int(mem[addr+bytes]));
	return v;
}

template<int i_ports, int d_ports>
sc_data Memory<i_ports,d_ports>::mem_d_write(const sc_addr& addr, const sc_data& data) {
	sc_data v;
	//assert(addr % (v.length() / 8) == 0); FIXME: should be here, but breaks sample solution; in fact, should just drop lower bits from the addr input to Memory (maybe create a sc_word_addr in const.h for this purpose).
	const int bytecount = v.length()/8;
	for(int bytes = 0; bytes < bytecount; ++bytes)
		mem[addr+bytes] = data.range((bytes+1)*8-1, (bytes)*8);
	return v;
}

template<int i_ports, int d_ports>
void Memory<i_ports,d_ports>::work() {
	if (reset) {
		return;
	}

	cache_delaybucket::oT ready;
	for(int port = 0; port < i_ports; ++port) {
		ready = i_resp.get();
		if (!ready) {
			i_ready[port] = false;
			continue;
		}
		i_ready[port] = true;
		i_tagout[port] = ready->first;
		i_data[port] = mem_i_read(ready->second);
	}
	for(int port = 0; port < d_ports; ++port) {
		ready = d_resp.get();
		if (!ready) {
			d_ready[port] = false;
			continue;
		}
		d_ready[port] = true;
		d_tagout[port] = ready->first;
		d_data[port] = mem_d_read(ready->second);
	}

	for(int port = 0; port < i_ports; ++port) {
		if (i_op[port] != NONE) {
			assert(i_op[port]==READ);
			int latency = 2;
			typename Cache::oV l1ov = L1i.get(i_addr[port]);
			if (!l1ov) {
				latency += 9;
				L1i.put(i_addr[port],CLEAN);
				typename Cache::oV l2ov = L2.get(i_addr[port]);
				if (!l2ov) {
					latency += 100;
					typename Cache::E l2e = L2.put(i_addr[port],CLEAN);
					if (l2e.second == DIRTY) ; // needs writeback
				}
			}
			assert(i_addr[port].read() < mem_size);
			i_resp.add(make_pair(i_tagin[port].read(), i_addr[port].read()), latency * ns);
		}
	}

	for(int port = 0; port < i_ports; ++port) {
		if (d_op[port] != NONE) {
			int latency = 3;
			typename Cache::oV l1ov = L1d.get(d_addr[port]);
			if (!l1ov) {
				latency += 9;
				typename Cache::E l1e = L1d.put(d_addr[port],d_op[port]==READ?CLEAN:DIRTY);
				if (l1e.second == DIRTY) {
					typename Cache::oV l2ov = L2.get(d_addr[port], false);
					if (!l2ov) {
						L2.put(d_addr[port],DIRTY);
					} else {
						*l2ov = DIRTY;
					}
				}
				typename Cache::oV l2ov = L2.get(d_addr[port]);
				if (!l2ov) {
					latency += 100;
					L2.put(d_addr[port],CLEAN);
				}
			} else {
				if (d_op[port] == WRITE) *l1ov = DIRTY;
			}
			assert(d_addr[port].read() < mem_size);
			if (d_op[port] == WRITE) mem_d_write(d_addr[port].read(), d_data[port].read());
			d_resp.add(make_pair(d_tagin[port].read(), d_addr[port].read()), latency * ns);
		}
	}

}

template<int i_ports, int d_ports>
Memory<i_ports,d_ports>::Memory(const sc_module_name &name, const char* filename)
	:	sc_module(name)
	,	L1i(128)
	,	L1d(128)
	,	L2(1024)
{
	mem_init(filename);
	SC_METHOD(work); sensitive << clk.pos();
}

template class Memory<1,1>;
template class Memory<1,2>;
template class Memory<2,1>;
template class Memory<2,2>;
template class Memory<2,3>;
template class Memory<2,4>;
