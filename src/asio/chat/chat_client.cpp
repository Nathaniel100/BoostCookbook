//
// Created by 吴凡 on 2017/3/17.
//



#include "chat_message.h"
#include <iostream>
#include <thread>
#include <deque>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using chat_message_queue = std::deque<chat_message>;

class chat_client {
public:
    chat_client(boost::asio::io_service &io_service, tcp::resolver::iterator endpoint) :
            io_service_{io_service}, socket_{io_service} {
        do_connect(endpoint);
    }

    void write(const chat_message &msg) {
        io_service_.post([this, msg]() {
            bool write_in_process = !write_messages_.empty();
            write_messages_.push_back(msg);
            if(!write_in_process) {
                do_write();
            }
        });
    }

    void close() {
        io_service_.post([this] { socket_.close(); });
    }

private:
    void do_connect(tcp::resolver::iterator endpoint) {
        boost::asio::async_connect(socket_, endpoint,
                                   [this](boost::system::error_code ec, tcp::resolver::iterator) {
                                       if (!ec) do_read_header();
                                   }
        );
    }

    void do_read_header() {
        boost::asio::async_read(socket_, boost::asio::buffer(read_message_.data(), read_message_.header_length),
                                [this](boost::system::error_code ec, std::size_t) {
                                    if (!ec && read_message_.decode_header()) {
                                        do_read_body();
                                    } else {
                                        socket_.close();
                                    }
                                }
        );
    }

    void do_read_body() {
        boost::asio::async_read(socket_, boost::asio::buffer(read_message_.body(), read_message_.body_length()),
                                [this](boost::system::error_code ec, std::size_t) {
                                    if (!ec) {
                                        std::cout.write(read_message_.body(), read_message_.body_length());
                                        std::cout << "\n";
                                        do_read_header();
                                    } else {
                                        socket_.close();
                                    }
                                }
        );
    }

    void do_write() {
        boost::asio::async_write(socket_, boost::asio::buffer(write_messages_.front().data(),
                                                              write_messages_.front().length()),
                                 [this](boost::system::error_code ec, std::size_t) {
                                     if(!ec) {
                                         write_messages_.pop_front();
                                         if(!write_messages_.empty()) {
                                             do_write();
                                         }
                                     } else {
                                         socket_.close();
                                     }
                                 }
        );
    }


    boost::asio::io_service &io_service_;
    tcp::socket socket_;
    chat_message read_message_;
    chat_message_queue write_messages_;
};

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "usage: chat_client <host> <port>";
        return 1;
    }

    try {
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator iterator = resolver.resolve(query);

        chat_client client(io_service, iterator);
        std::thread thread([&io_service] { io_service.run(); });

        char message[chat_message::max_body_length + 1] = {0};
        while (std::cin.getline(message, chat_message::max_body_length + 1)) {
            chat_message msg;
            msg.body_length(strlen(message));
            memcpy(msg.body(), message, msg.body_length());
            msg.encode_header();
            client.write(msg);
        }

        client.close();
        thread.join();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

