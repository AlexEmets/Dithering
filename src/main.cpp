#include <sstream>
#include"image_processing.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include<boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include"server.h"
#include"client.h"



namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>




auto const host = "localhost";
auto const port = "8080";
auto const target = "localhost/8080";
int version = 11;


boost::asio::streambuf getHttpRequest() {
//    boost::asio::streambuf request;
//    std::ostream request_stream(&request);
//    request_stream << "POST " << " HTTP/1.1\r\n";
//    request_stream << "Host: " << "localhost:8080" << "\r\n";
//    request_stream << "Content-Type: text/plain; charset=utf-8 \r\n";
//    request_stream << "Content-Length: " << 100 << "\r\n";
//    request_stream << "Connection: close\r\n\r\n";



  //  return request;
//    std::string ret;
//    // Convert streambuf to std::string
//    std::istream(&request) >> ret;

 //   return ret;
}
int main() {

//    boost::asio::streambuf http_request;
//    std::ostream request_stream(&http_request);

//    request_stream << "POST /dither HTTP/1.1\r\n";
//    request_stream << "Host: localhost:8080\r\n";
//    request_stream << "Content-Type: multipart/form-data;boundary=\"boundary\"\r\n";
//    request_stream <<"--boundary\r\n";
//    request_stream <<"Content-Disposition: form-data; name=\"field1\"\r\n";
//    request_stream <<"value1\r\n";
//    request_stream <<"--boundary\r\n";
//    request_stream <<"Content-Disposition: form-data; name=\"field2\"; filename=\"example.txt\"\r\n";

    std::thread mainServerThread(mainServerFunc);

//    std::thread mainClientThread(mainClientFunc);
//    mainClientThread.detach();

    mainClientFunc();
    mainServerThread.join();

    std::cout << "Server finished." << std::endl;


}


























//    std::string inputFileName("/home/oleksandr/Dithering/assets/original.jpg");
//    std::string outputFileName("/home/oleksandr/Dithering/outputs/dithered.jpg");
//
//    colorToGreyScale(inputFileName, outputFileName);

//    return EXIT_FAILURE;
//}

