//
// Created by 吴凡 on 2017/3/16.
//


#include <boost/asio.hpp>
#include <iostream>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

using boost::asio::ip::tcp;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: client <host>" << std::endl;
        return 1;
    }
    try {
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], boost::lexical_cast<std::string>(13003));
        tcp::resolver::iterator iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, iterator);

        for (;;) {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }
            std::cout.write(buf.data(), len);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}