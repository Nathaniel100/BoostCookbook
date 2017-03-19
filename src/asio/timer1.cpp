//
// Created by 吴凡 on 2017/3/11.
//

#include <boost/asio.hpp>
#include <iostream>


// Using a timer synchronously

int main() {
    boost::asio::io_service io;

    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));
    timer.wait();

    std::cout << "Hello World!\n";
    return 0;
}

