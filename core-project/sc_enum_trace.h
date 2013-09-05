// sc_enum_trace.h
//
// Copyright (c) 2010, OFFIS Institute for Information Technology
// All rights reserved.
//
// Trace enumerated types in SystemC
// Author: Philipp A. Hartmann <philipp.hartmann@xxxxxxxx>
//
// The contents of this file are subject to the restrictions and limitations
// set forth in the SystemC Open Source License Version 3.0 (the "License");
// You may not use this file except in compliance with such restrictions and
// limitations. You may obtain instructions on how to receive a copy of the
// License at http://www.systemc.org/. Software distributed by Contributors
// under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
// ANY KIND, either express or implied. See the License for the specific
// language governing rights and limitations under the License.

#ifndef SC_ENUM_TRACE_H_INCLUDED_
#define SC_ENUM_TRACE_H_INCLUDED_

#include <systemc>
#include <tr1/type_traits>  // is_enum

namespace sc_core {

namespace impl {

  // detect enumerated types
  using std::tr1::is_enum;

  // enable_if for SFINAE
  template<bool Cond, typename T = void >
    struct enable_if_c {};
  template<typename T>
    struct enable_if_c<true,T> { typedef T type; };
  template<typename Cond, typename T = void >
    struct enable_if : enable_if_c< Cond::value, T > {};

  // select appropriate integral type for enum
  template< int Size > struct enum_plain_selector;

# define SC_ENUM_PLAIN_SELECTION(Type) \
  template<> struct enum_plain_selector<sizeof(Type)> { typedef Type type; }

  SC_ENUM_PLAIN_SELECTION(unsigned char);
  SC_ENUM_PLAIN_SELECTION(unsigned short);
  SC_ENUM_PLAIN_SELECTION(unsigned int);
  SC_ENUM_PLAIN_SELECTION(sc_dt::uint64);

# undef SC_ENUM_PLAIN_SELECTION

  template<typename T> struct enum_plain_type
    { typedef typename enum_plain_selector< sizeof(T) >::type type; };

} // namespace impl

// sc_trace for enumerated types (uses SFINAE to exclude non-enums)
template<typename T>
typename impl::enable_if< impl::is_enum<T> >::type
sc_trace( sc_trace_file* tf, T const & e, std::string const& name )
{
  typedef typename impl::enum_plain_type<T>::type plain_type;
  sc_trace( tf, reinterpret_cast< plain_type const& >(e), name );
}

} // namespace sc_core

#endif // SC_ENUM_TRACE_H_INCLUDED_
