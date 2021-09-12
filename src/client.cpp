#include "client.h"
#include<array>
#include<boost/asio.hpp>
#include<iostream>

void mainClientFunc() {
    using boost::asio::ip::tcp;

    boost::asio::io_context ioc;

    tcp::resolver resolver(ioc);

    auto endpoints = resolver.resolve("localhost", "8080");

    tcp::socket socket(ioc);

    boost::asio::connect(socket, endpoints);

   while(true) {
        std::array<char, 4096> buf{};
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if(error == boost::asio::error::eof) {
            break;
        }
        else if(error){
            throw boost::system::system_error(error);
        }
       // std::cout.write(buf.data(), static_cast<int>(len));

        std::cout << buf.data();

   }
}