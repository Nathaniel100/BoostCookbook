//
// Created by 吴凡 on 2017/3/16.
//
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using namespace std;
    time_t daytime = time(nullptr);
    return ctime(&daytime);
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13003));
        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::string daytime = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(daytime), ignored_error);
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}