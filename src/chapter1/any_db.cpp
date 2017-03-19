//
// Created by 吴凡 on 2017/3/7.
//

#include <boost/any.hpp>
#include <vector>
#include <iostream>

using cell_t = boost::any;
using row_t = std::vector<cell_t>;

row_t query_row(const char* query) {
    row_t r;
    r.push_back(10);
    r.push_back(10.1f);
    r.push_back(std::string("Hello"));
    return r;
}

class DBSum : public std::unary_function<cell_t , void> {
public:
    DBSum(double& sum):sum_{sum}{}
    void operator()(const cell_t& v) {
        const std::type_info &type = v.type();
        if(type == typeid(int)) {
            sum_ += boost::any_cast<int>(v);
        } else if(type == typeid(float)) {
            sum_ += boost::any_cast<float>(v);
        }
    }
private:
    double& sum_;
};

int main() {
    row_t row = query_row("Please give me some row");
    double sum = 0.0;
    std::for_each(row.begin(), row.end(), DBSum(sum));
    std::cout << "Sum:" << sum << "\n";
    return 0;
}

