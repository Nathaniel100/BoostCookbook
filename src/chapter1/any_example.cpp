//
// Created by 吴凡 on 2017/3/5.
//

#include <boost/any.hpp>
#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<boost::any> some_values;
    some_values.push_back(10);
    const char *string_value = "Hello World";
    some_values.push_back(boost::any(string_value));
    some_values.push_back(std::string("Wow!"));

    std::string &str = boost::any_cast<std::string&>(some_values.back());
    str += "Any";
    std::cout << str << "\n";
    return 0;
}

