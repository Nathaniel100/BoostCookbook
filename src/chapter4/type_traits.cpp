//
// Created by 吴凡 on 2017/3/20.
//

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <iostream>


template<class T1, class T2>
void type_traits_example(T1& /*t1*/, T2& /*t2*/) {
    std::cout << boost::is_unsigned<T1>::value << "\n";
    std::cout << boost::is_same<T1, T2>::value << "\n";
    typedef typename boost::remove_const<T1>::type t1_nonconst_t;
};
