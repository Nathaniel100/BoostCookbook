//
// Created by 吴凡 on 2017/3/9.
//

#include <boost/numeric/conversion/cast.hpp>
#include <iostream>

int getVersion1() {
    return -1;
}

int getVersion2() {
    return 1000;
}

int getVersion3() {
    return 1000000;
}

// There's more
template<class Source, class Target>
struct MyThrowOverflowHandler {
    void operator()(boost::numeric::range_check_result r) {
        if(r != boost::numeric::cInRange) {
            throw std::logic_error("Not in range");
        }
    }
};

template<class Target, class Source>
Target MyNumericCast(const Source& in) {
    using convTraits = boost::numeric::conversion_traits<Target, Source>;
    using castTraits = boost::numeric::numeric_cast_traits<Target, Source>;
    using converter = boost::numeric::converter<Target, Source, convTraits, MyThrowOverflowHandler<Source, Target>>;
    return converter::convert(in);
};

int main() {
    uint16_t v1 = static_cast<uint16_t>(getVersion1());
    uint16_t v2 = static_cast<uint16_t>(getVersion2());
    uint16_t v3 = static_cast<uint16_t>(getVersion3());
    std::cout << v1 << " " << v2 << " " << v3 << "\n";

    v1 = v2 = v3 = 0;
    // so we need numeric_cast
    try {
        v1 = boost::numeric_cast<uint16_t>(getVersion1());
    } catch (const boost::numeric::negative_overflow &e) {
        std::cout << "getVersion1 failed: " << e.what() << "\n";
    }

    v2 = boost::numeric_cast<uint16_t>(getVersion2());

    try {
        v3 = boost::numeric_cast<uint16_t>(getVersion3());
    } catch (const boost::numeric::positive_overflow &e) {
        std::cout << "getVersion3 failed: " << e.what() << "\n";
    }
    std::cout << v1 << " " << v2 << " " << v3 << "\n";

    try {
        MyNumericCast<short>(1000000);
    } catch (const std::logic_error& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}

