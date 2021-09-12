#include<boost/asio.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include"client.h"

void startBrowser() {

    std::string h = "xdg-open http://localhost:" + std::to_string(8080) + "/";

    std::system(h.c_str());
}

void mainServerFunc() {

    using boost::asio::ip::tcp;

    //startBrowser();

    try{
        boost::asio::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint (tcp::v4(), 8080));
        //std::string prefix = "FROM SERVER>";
       // while(true) {

            std::cout <<  "Accepting connection on port 8080\n";

            tcp::socket socket(ioc);
            acceptor.accept(socket);

            std::cout <<  "Connection accepted!\n";



           // mainClientFunc();


            std::string answerMessage = "HELLO CLIENT!\n";
            boost::system::error_code error;

            boost::asio::write(socket, boost::asio::buffer(answerMessage), error);
        //std::thread clientThread(mainClientFunc);
        //clientThread.detach();
            //clientThread.detach();
       // }
    }catch(const std::exception& exc) {
        std::cout << exc.what() << '\n';
    }

}