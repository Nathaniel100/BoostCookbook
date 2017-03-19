//
// Created by 吴凡 on 2017/3/7.
//

#include <boost/variant.hpp>
#include <vector>
#include <iostream>
#include <string>

using cell_t = boost::variant<int, float, std::string>;
using row_t = std::vector<cell_t>;

row_t query_row(const char* query) {
    row_t row;
    row.push_back(10);
    row.push_back(10.1f);
    row.push_back(std::string("Hello"));
    return row;
}

class DBSumVisitor : public boost::static_visitor<double> {
public:
    double operator()(int v) {
        return v;
    }
    double operator()(float v) {
        return v;
    }
    double operator()(const std::string& s) {
        return 0.0;
    }
};

int main() {
    row_t row = query_row("Please give me some row");
    double sum = 0.0;
    DBSumVisitor visitor;
    for(auto it = row.begin(); it != row.end(); ++it) {
        sum += boost::apply_visitor(visitor, *it);
    }
    std::cout << "Sum is: " << sum << "\n";
    return 0;
}

