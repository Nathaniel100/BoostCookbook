//
// Created by 吴凡 on 2017/3/21.
//

#include <vector>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/static_assert.hpp>


template<class T>
struct IsVector : public boost::false_type {};

template<class T, class Allocator>
struct IsVector<std::vector<T, Allocator>> : public boost::true_type {};


int main() {
    BOOST_STATIC_ASSERT(IsVector<std::vector<int>>::value);
    BOOST_STATIC_ASSERT(!IsVector<int>::value);
    return 0;
}