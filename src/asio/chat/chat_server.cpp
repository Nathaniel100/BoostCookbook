//
// Created by 吴凡 on 2017/3/17.
//

#include "chat_message.h"
#include <boost/asio.hpp>
#include <deque>
#include <set>
#include <iostream>
#include <list>

using boost::asio::ip::tcp;
using chat_message_queue = std::deque<chat_message>;

class chat_participant {
public:
    virtual ~chat_participant() {}

    virtual void deliver(const chat_message &msg) = 0;
};

using chat_participant_ptr = std::shared_ptr<chat_participant>;

class chat_room {
public:
    void join(chat_participant_ptr participant) {
        participants_.insert(participant);
        for (auto msg: recent_msgs_) {
            participant->deliver(msg);
        }
    }

    void left(chat_participant_ptr participant) {
        participants_.erase(participant);
    }

    void deliver(const chat_message &msg) {
        recent_msgs_.push_back(msg);
        while (recent_msgs_.size() > max_recent_msgs) {
            recent_msgs_.pop_front();
        }
        for (auto participant: participants_) {
            participant->deliver(msg);
        }
    }

private:
    std::set<chat_participant_ptr> participants_;
    enum {
        max_recent_msgs = 100
    };
    chat_message_queue recent_msgs_;
};

class chat_session : public chat_participant, public std::enable_shared_from_this<chat_session> {
public:
    chat_session(tcp::socket socket, chat_room &room) : socket_{std::move(socket)}, room_{room} {}

    void start() {
        room_.join(shared_from_this());
        do_read_header();
    }

    void deliver(const chat_message &msg) {
        bool write_in_progress = !write_messages_.empty();
        write_messages_.push_back(msg);
        if (!write_in_progress) {
            do_write();
        }
    }

private:
    void do_read_header() {
        boost::asio::async_read(socket_, boost::asio::buffer(read_message_.data(), chat_message::header_length),
                                [this](boost::system::error_code ec, std::size_t) {
                                    if (!ec && read_message_.decode_header()) {
                                        do_read_body();
                                    } else {
                                        room_.left(shared_from_this());
                                    }
                                }
        );
    }

    void do_read_body() {
        boost::asio::async_read(socket_, boost::asio::buffer(read_message_.body(), read_message_.body_length()),
                                 [this](boost::system::error_code ec, std::size_t) {
                                     if (!ec) {
                                         room_.deliver(read_message_);
                                         do_read_header();
                                     } else {
                                         room_.left(shared_from_this());
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
                                         room_.left(shared_from_this());
                                     }
                                 }
        );
    }

    tcp::socket socket_;
    chat_room &room_;
    chat_message read_message_;
    chat_message_queue write_messages_;
};

class chat_server {
public:
    chat_server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint):
            acceptor_{io_service, endpoint}, socket_{io_service} {
        do_accept();
    }
private:
    void do_accept() {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if(!ec) {
                std::make_shared<chat_session>(std::move(socket_), room_)->start();
            }
            do_accept();
        });
    }
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    chat_room room_;
};


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Usage: chat_server <port> [<port>...]\n";
        return 1;
    }
    try {
        boost::asio::io_service io_service;
        std::list<chat_server> servers;
        for (int i = 1; i < argc; ++i) {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}