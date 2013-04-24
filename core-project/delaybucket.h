#ifndef _DELAY_BUCKET
#define _DELAY_BUCKET

#include <systemc>
#include <queue>
#include <vector>
#include <boost/optional.hpp>

template<typename T>
class delaybucket {
	typedef std::pair<sc_core::sc_time, T> val_t;
	struct Comp {
		bool operator()(const val_t& l, const val_t& r) {
			return l.first >= r.first;
		}
	};
	std::priority_queue<val_t, std::vector<val_t>, Comp> pq;
public:
	void add(const T& v, sc_core::sc_time delay) {
		sc_core::sc_time when = sc_core::sc_time_stamp() + delay;
		pq.push(std::make_pair(when, v));
	}
	typedef boost::optional<T> oT;
	oT get() {
		if (pq.empty()) return boost::none;
		sc_core::sc_time now = sc_core::sc_time_stamp();
		if (pq.top().first <= now) {
			const T top = pq.top().second;
			pq.pop();
			return top;
		}
		return boost::none;
	}
};

#endif
