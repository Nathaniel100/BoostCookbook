//
// Created by 吴凡 on 2017/3/11.
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

// Using a member function as a handler

class Printer {
public:
    Printer(boost::asio::io_service &io): t_{io, boost::posix_time::seconds(1)}, count_{0} {
        t_.async_wait(boost::bind(&Printer::print, this));
    }

    ~Printer() {
        std::cout << "Final count: " << count_ << "\n";
    }

    void print() {
        if(count_ < 5) {
            std::cout << "Count: " << count_ << "\n";
            count_++;

            t_.expires_at(t_.expires_at() + boost::posix_time::seconds(1));
            t_.async_wait(boost::bind(&Printer::print, this));
        }
    }

private:
    boost::asio::deadline_timer t_;
    int count_;
};

int main() {
    boost::asio::io_service io;
    Printer printer(io);

    io.run();
    return 0;
}

