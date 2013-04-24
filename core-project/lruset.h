#ifndef _LRUSET_H
#define _LRUSET_H

#include <boost/optional.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>

template<typename K, typename V>
class lruset {
	int capacity;
	typedef boost::bimap<boost::bimaps::set_of<K>, boost::bimaps::list_of<V> > S;
	S s;
public:
	lruset(const int capacity): capacity(capacity) { }
	typedef boost::optional<V&> oV;
	oV get(const K& k, bool promote = true) {
		typename S::left_iterator i = s.left.find(k);
		if (i == s.left.end()) {
			return boost::none;
		}
		if (promote) s.right.relocate(s.right.end(), s.project_right(i));
		return i->second;
	}
	typedef const std::pair<K,V> E;
	E put(const K& k, const V& v) {
		std::pair<K,V> victim;
		if (s.size() == capacity) {
			victim = std::make_pair(s.right.begin()->second, s.right.begin()->first);
			s.right.erase(s.right.begin());
		}
		s.insert(typename S::value_type(k,v));
		return victim;
	}
};

#endif
