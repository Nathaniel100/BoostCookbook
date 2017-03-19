//
// Created by 吴凡 on 2017/3/13.
//

#include <boost/lexical_cast.hpp>
#include <iostream>

class NegativeNumber {
public:
    NegativeNumber(): number_{0} {}
    explicit NegativeNumber(unsigned int number): number_(number) {}
    NegativeNumber(const NegativeNumber& n): number_{n.number_} {}
    NegativeNumber& operator=(const NegativeNumber& n) {
        this->number_ = n.number_;
        return *this;
    }
    unsigned int ValueWithoutSign() const {
        return number_;
    }
    NegativeNumber(NegativeNumber&& n): number_{n.number_} {
        n.number_ = 0;
    }
    NegativeNumber& operator=(NegativeNumber&& n) {
        std::swap(number_, n.number_);
        return *this;
    }
private:
    unsigned int number_;
};

std::ostream& operator<<(std::ostream& out, const NegativeNumber& n) {
    out << "-" << n.ValueWithoutSign();
    return out;
}

std::istream& operator>>(std::istream& in, NegativeNumber& n) {
    char ch;
    in >> ch;
    if(ch != '-') {
        throw std::logic_error("Negative number must start with -");
    }
    unsigned int i;
    in >> i;
    n = NegativeNumber(i);
    return in;
}

int main() {
    NegativeNumber n = boost::lexical_cast<NegativeNumber>("-100");
    std::cout << "NegativeNumber n: " << n << "\n";
    int i = boost::lexical_cast<int>(n);
    assert(i == -100);
    boost::array<char, 10> a = boost::lexical_cast<boost::array<char, 10>>(n);
    assert(a[0] == '-');
    assert(a[1] == '1');
    assert(a[2] == '0');
    assert(a[3] == '0');
    assert(a[4] == '\0');
    return 0;
}

