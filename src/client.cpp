#include <cstdlib>
#include <cstring>
#include <iostream>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: async_client <num_threads> <read_write_cycles>\n";
      return 1;
    }

    int num_threads = std::stoi(argv[1]);
    std::cout << "Number of clients: " << num_threads << std::endl;
    int read_write_cycles = std::stoi(argv[2]);
    std::cout << "Read/Write cycles: " << read_write_cycles << std::endl;

    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    const std::string HOST = "localhost";
    const std::string PORT = "9000";
    const std::string MESSAGE = "Знакомство с асинхронным вводом/выводом";

    for (int i = 0; i < num_threads; i++) {
        boost::asio::connect(s, resolver.resolve(HOST, PORT));
        for (int j = 0; j < read_write_cycles; j++) {
            std::cout << "Enter message: " << std::endl;
            char request[max_length];
            //std::cin.getline(request, max_length);
            size_t request_length = std::strlen(request);
            boost::asio::write(s, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_length));
            std::cout << "Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        }
        std::cout << "Client disconnect" << std::endl;
    }
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
