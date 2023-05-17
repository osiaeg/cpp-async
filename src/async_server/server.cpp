#include <iostream>
#include <memory>
#include <utility>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class session: public std::enable_shared_from_this < session > {
public: session(tcp::socket socket, int num): socket_(std::move(socket)) {
        this -> num_ = num;
    }

    void start() {
        do_read();
    }

private: void connection_lost() const {
        std::cout << "connection lost: " << num_ << std::endl;
    }

    void do_read() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length) {
                                    if (!ec) {
                                        do_write(length);
                                    } else if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset) {
                                        connection_lost();
                                    }
                                });
    }

    void do_write(std::size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/ ) {
                                     if (!ec) {
                                         do_read();
                                     }
                                 });

    }

    tcp::socket socket_;
    int num_;
    enum { max_length = 1024 };
    char data_[max_length] {};
};

class server {
public: server(boost::asio::io_context & io_context, short port): acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private: void do_accept() {
        acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket) {

                    if (!ec) {
                        ++client_num;
                        std::shared_ptr < session > Session = std::make_shared < session > (std::move(socket), client_num);
                        Session -> start();
                        std::cout << "connection established: " << client_num << std::endl;
                    }

                    do_accept();
                });
    }

    int client_num { 0 };
    tcp::acceptor acceptor_;
};

int main() {
    try {

        boost::asio::io_context io_context;

        short port = 9000;
        server s(io_context, port);
        io_context.run();

    } catch (std::exception & e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}