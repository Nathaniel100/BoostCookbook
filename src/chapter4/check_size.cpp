//
// Created by 吴凡 on 2017/3/20.
//

#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <string>
#include <iostream>

template<class T, size_t BufSize>
void serialize(const T& value, boost::array<uint8_t, BufSize>& buffer) {
    // TODO fixme
    // 1. no check buffer size, may overflow
    // 2. can be used with non-plain old data(POD), which result in incorrect behavior
    std::memcpy(&buffer[0], &value, sizeof(T));
};

template<class T, size_t BufSize>
void serialize_fix1(const T& value, boost::array<uint8_t, BufSize>& buffer) {
    assert(BufSize >= sizeof(T)); // a bad solution, can be checked in compile time
    std::memcpy(&buffer[0], &value, sizeof(T));
};


template<class T, size_t BufSize>
void serialize_fix(const T& value, boost::array<uint8_t, BufSize>& buffer) {
    BOOST_STATIC_ASSERT(BufSize >= sizeof(T));
    BOOST_STATIC_ASSERT(boost::is_pod<T>::value);
    std::memcpy(&buffer[0], &value, sizeof(T));
};

class C2 {
public:
    void hello() {
        std::cout << msg << "\n";
    }
private:
    std::string msg{"hello"};
};

int main() {
    BOOST_STATIC_ASSERT(boost::is_pod<std::string>::value);
    int value = 100;
    boost::array<uint8_t, 4> buffer;
    serialize_fix(value, buffer);

    C2 c2;
    boost::array<uint8_t, 100> buffer2;
    serialize_fix(c2, buffer2);

    return 0;
}
