//
// Created by 吴凡 on 2017/3/5.
//

#include <boost/variant.hpp>
#include <vector>
#include <string>
#include <iostream>

int main() {
    using var = boost::variant<int, const char*, std::string>;
    std::vector<var> some_values;
    some_values.push_back(10);
    const char *p = "Hello World";
    some_values.push_back(p);
    some_values.push_back(std::string("Wow!"));

    std::string& str = boost::get<std::string&>(some_values.back());
    str += " That's great.";
    std::cout << str << "\n";
    return 0;
}
