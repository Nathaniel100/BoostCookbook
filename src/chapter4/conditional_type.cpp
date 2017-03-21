//
// Created by 吴凡 on 2017/3/21.
//

/*
 *
 * template<class T>
 * void inc(T& t) {
 *  // ++t ?
 *  // or t++ ?
 *  // or t += T(1) ?
 *  // or t = t + T(1)
 * }
 *
 */


#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/has_pre_increment.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <iostream>

namespace detail {

struct PreIncFunctor {
    template<class T> void operator()(T& t) {
        ++t;
    }
};

struct PostIncFunctor {
    template<class T> void operator()(T& t) {
        t++;
    }
};

struct PlusAssignFunctor {
    template<class T> void operator()(T& t) {
        t += T(1);
    }
};

struct PlusFunctor {
    template<class T> void operator()(T& t) {
        t = t + T(1);
    }
};

}

template<class T>
void inc(T& t) {
    using plus1_t = detail::PlusFunctor;

    using plus2_t = typename boost::conditional<boost::has_plus_assign<T>::value, detail::PlusAssignFunctor, plus1_t>::type;

    using plus3_t = typename boost::conditional<boost::has_post_increment<T>::value, detail::PostIncFunctor, plus2_t>::type;

    using plus4_t = typename boost::conditional<boost::has_pre_increment<T>::value, detail::PreIncFunctor, plus3_t>::type;

    plus4_t()(t);
}

int main() {
    int i = 0;
    inc(i);
    std::cout << "i: " << i << "\n";
    return 0;
}






