#include <iostream>
#include "boost/asio.hpp"
#include <thread>

using boost::asio::ip::tcp;

enum {
    max_length = 1024
};
const std::string HOST = "localhost";
const std::string PORT = "9000";

void connect_client(boost::asio::io_context & context, int cycles) {
    tcp::socket s(context);
    tcp::resolver resolver(context);
    boost::asio::connect(s, resolver.resolve(HOST, PORT));

    for (int i = 0; i < cycles; i++) {
        std::string request{"Hello"};
        size_t request_length = request.length();
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length] { 0 };
        boost::asio::read(s, boost::asio::buffer(reply, request_length));
    }

}

int main(int argc, char * argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: async_client <num_threads> <read_write_cycles>\n";
            return 1;
        }

        int num_threads = std::stoi(argv[1]);
        int read_write_cycles = std::stoi(argv[2]);

        boost::asio::io_context io_context;

        std::vector<std::thread> threads(num_threads);
        for (int i = 0; i < num_threads; i++) {
            threads[i] = std::thread(connect_client, std::ref(io_context), read_write_cycles);
        }
        for (auto& th : threads) {
            th.join();
        }
    } catch (std::exception & e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}