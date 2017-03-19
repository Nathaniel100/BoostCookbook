//
// Created by 吴凡 on 2017/3/13.
//

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

struct Date {
    unsigned short year_;
    unsigned short month_;
    unsigned short day_;
};

Date ParseDate(const std::string& s) {
    using boost::spirit::qi::ushort_;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::_1;
    using boost::phoenix::ref;
    Date date;
    const char *first = s.data();
    const char *end = s.data() + s.length();
    bool success = boost::spirit::qi::parse(first, end, ushort_[ref(date.year_) = _1] >> char_('-')
        >> ushort_[ref(date.month_) = _1] >> char_('-') >> ushort_[ref(date.day_) = _1]);
    if(!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return date;
}

int main() {
    Date date = ParseDate("2012-12-31");
    assert(date.year_ == 2012);
    assert(date.month_ == 12);
    assert(date.day_ == 31);
    return 0;
}

