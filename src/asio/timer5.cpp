//
// Created by 吴凡 on 2017/3/11.
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>


class Printer {
public:
    Printer(boost::asio::io_service &io) :
            strand_{io},
            t1_{io, boost::posix_time::seconds(1)},
            t2_{io, boost::posix_time::seconds(1)},
            count_{0} {
        t1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
        t2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
    }

    ~Printer() {
        std::cout << "Final count: " << count_ << "\n";
    }

    void print1() {
        if (count_ < 10) {
            std::cout << "Timer1 count: " << count_ << "\n";
            count_++;

            t1_.expires_at(t1_.expires_at() + boost::posix_time::seconds(1));
            t1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
        }
    }

    void print2() {
        if (count_ < 10) {
            std::cout << "Timer2 count: " << count_ << "\n";
            count_++;

            t1_.expires_at(t1_.expires_at() + boost::posix_time::seconds(1));
            t1_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
        }
    }

private:
    boost::asio::io_service::strand strand_;
    boost::asio::deadline_timer t1_;
    boost::asio::deadline_timer t2_;
    int count_;
};


int main() {
    boost::asio::io_service io;
    Printer printer(io);
    boost::thread t{boost::bind(&boost::asio::io_service::run, &io)};
    io.run();
    t.join();
    return 0;
}

