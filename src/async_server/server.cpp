#include <iostream>
#include <memory>
#include <utility>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class session: public std::enable_shared_from_this < session > {
public:
    session(tcp::socket socket, int num): socket_(std::move(socket)), num_(num) {
        std::cout << "connection established: " << num_ << std::endl;
    }

    ~session(){
        std::cout << "connection lost: " << num_ << std::endl;
    }

    void start() {
        do_read();
    }

private:

    void do_read() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length) {
                                    if (!ec) {
                                        do_write(length);
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

    int num_;
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length] {};
};

class server {
public:
    server(boost::asio::io_context & io_context, short port): acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket) {

                    if (!ec) {
                        std::make_shared < session > (std::move(socket), ++client_num) -> start();
                    }

                    do_accept();
                });
    }

    int client_num { 0 };
    tcp::acceptor acceptor_;
};

int main() {
    try {
        const short PORT = 9000;
        boost::asio::io_context io_context;

        server s(io_context, PORT);
        io_context.run();

    } catch (std::exception & e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}