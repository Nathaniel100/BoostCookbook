//
// Created by 吴凡 on 2017/3/9.
//

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <set>

int string2number(const std::string &s) {
    int i;
    std::istringstream iss(s);
    iss >> i;
    return i;
}

template<class Container>
std::vector<long> Container2Longs(const Container &container) {
    std::vector<long> values;
    std::transform(container.begin(), container.end(), std::back_inserter(values),
                   [](const typename Container::value_type &t) {
                       return boost::lexical_cast<long>(t);
                   });
    return values;
}

int main() {
    std::string s("100");
    int i = 0, j = 0;
    i = string2number(s);
    j = boost::lexical_cast<int>(s);
    assert(i == j);

    std::string s2("100hello");
    try {
        j = boost::lexical_cast<int>(s2);
        std::cout << "100hello convert to number: " << j << "\n";
    } catch (const boost::bad_lexical_cast &e) {
        std::cout << e.what() << "\n";
    }

    std::string s3("hello100");
    try {
        j = boost::lexical_cast<int>(s3);
        std::cout << "hello100 convert to number: " << j << "\n";
    } catch (const boost::bad_lexical_cast &e) {
        std::cout << e.what() << "\n";
    }
    i = string2number(s2);
    std::cout << "100hello(istringstream) convert to number: " << i << "\n";
    i = string2number(s3);
    std::cout << "hello100(istringstream) convert to number: " << i << "\n";

    std::set<std::string> set1{"123", "4", "56", "-1"};
    std::vector<long> values1 = Container2Longs(set1);
    std::for_each(values1.begin(), values1.end(), [](long l) { std::cout << l << " "; });
    std::cout << "\n";
}
