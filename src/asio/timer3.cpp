//
// Created by 吴凡 on 2017/3/11.
//

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

// Binding arguments to a handler

void print(const boost::system::error_code& /*e*/, boost::asio::deadline_timer *t, int *count) {
    if(*count < 5) {
        std::cout << "count: " << *count << '\n';
        *count += 1;

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
    }
}

int main() {
    int count = 0;
    boost::asio::io_service io;

    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));
    timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &count));

    io.run();

    std::cout << "Final count: " << count << "\n";
    return 0;
}
