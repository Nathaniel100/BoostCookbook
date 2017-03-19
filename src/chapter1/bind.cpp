//
// Created by 吴凡 on 2017/3/8.
//

#include <vector>
#include <functional>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/array.hpp>

struct Number {
    int i_;
    Number(int i = 0): i_{i} {}
    friend std::ostream& operator<<(std::ostream &out, Number n) {
        out << n.i_;
        return out;
    }
};

inline Number operator+(Number n1, Number n2) {
    return n1.i_ + n2.i_;
}

struct Multi2Func : std::unary_function<Number&, Number&> {
    Number& operator()(Number& n) {
        n = n+n;
        return n;
    }
};

template<class Iterator>
void print(Iterator begin, Iterator end) {
    for(Iterator it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<Number> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(numbers.begin(), numbers.end());
    std::for_each(numbers.begin(), numbers.end(), Multi2Func());
    print(numbers.begin(), numbers.end());
    std::for_each(numbers.begin(), numbers.end(), boost::bind(std::plus<Number>(), _1, _1));
    print(numbers.begin(), numbers.end());

    boost::array<int, 12> values = {1, 2, 3, 4, 5, 6, 7, 100, 99, 98, 97, 96};
    auto count0 = std::count_if(values.begin(), values.end(), std::bind1st(std::less<int>(), 5));
    auto count1 = std::count_if(values.begin(), values.end(), boost::bind(std::less<int>(), 5, _1));
    assert(count0 == count1);

    boost::array<std::string, 3>  str_values = {{"We ", "are", " the champions!"}};
    auto count2 = std::count_if(str_values.begin(), str_values.end(), std::mem_fn(&std::string::empty));
    auto count3 = std::count_if(str_values.begin(), str_values.end(), boost::bind(&std::string::empty, _1));
    assert(count3 == 3);
}