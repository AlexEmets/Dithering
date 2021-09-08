#include<iostream>
#include <regex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <unistd.h>
#include <thread>

bool needStop = false;
int port = 8080;
const int MAX_PORT = 10000;

int clientsCount = 0;


std::string getHttpResponse(const std::string &textResponse, const std::string &contentType) {
    std::string result =
            "HTTP/1.1 200 OK\n"
            "Content-Type: " + contentType + "; charset=utf-8\n"
                                             "Access-Control-Allow-Origin: *\n"
                                             "Content-Length: " + std::to_string(textResponse.length() + 2) + "\n\n" +
            textResponse + "\n\n";

    return result;
}



std::string getRequestData(std::string data) {
    if(data.length() > 0) {
        size_t pos1 = data.find(' ');
        size_t pos2 = data.find(' ', pos1+1);

        data = data.substr(pos1 + 1, pos2 - pos1 - 1);

        if(data[0] == '/') {
            data = data.substr(1);
        }

        return data;
    }
    else return "";
}

std::pair<std::string, std::string> processRequest(const std::string &requestData) {

    std::pair<std::string, std::string> result;
    if(requestData == "") {
        std::stringstream buf;

        std::ifstream f("web/interface.html");
        if(f.is_open()) {
            buf << f.rdbuf();
        }
        else {
            std::ifstream f2("../web/interface.html");
            if(f2.is_open()) {
                buf << f2.rdbuf();
            }
        }

        result.first = buf.str();
        result.first = std::regex_replace(result.first, std::regex("8080"), std::to_string(port));

        result.second = "text/html";
    }
    else if(requestData == "favicon.ico") {
        result.first = "";
        result.second = "text/html";
    }
    else if(requestData == "exit") {
        result.first = "confirmed";
        result.second = "text/plain";
        needStop = true;
        std::cout << "Exit requested " << std::endl;
    }
    else {
        unsigned long long inputNumber = std::stoull(requestData);

        if (inputNumber != 0) {
            unsigned long long f = 5;
            result.first = std::to_string(f);
            result.second = "text/plain";
        }
    }
    return result;
}

int clientThread(int newsockfd, int clientId) {
    int res;
    std::string requestString;

    // TODO: receive data from the request (HTTP protocol) to requestString.
    do {
        int sz = 32;
        char *data = new char[sz+1]{0};

        res = recv(newsockfd, data, sz, 0);

        requestString += data;
        if (requestString.find("\n\n") >= 0) {
            break;
        }
    } while (res != 0);

    // Request parsing and response string and type generation
    // Look inside to understand the data needed (if needed)
    std::string requestData = getRequestData(requestString);
    auto responseInfo = processRequest(requestData);

    res = 0;

    // Create correct HTTP response
    std::string response = getHttpResponse(
            responseInfo.first,
            responseInfo.second
    );

    // TODO: send response to client
    res = send(newsockfd, response.c_str(), response.length(),0);
    close(newsockfd);

    return 0;
}

void startBrowser() {

    std::string h = "xdg-open http://localhost:" + std::to_string(port) + "/";

    std::system(h.c_str());
}

int mainServerThreadRoutine() {
    // TODO: bind socket to port (from 'port' global variable) and start listening for connections.
    //  If port is busy, try port++ until succeeded
    //  Create processing thread for each new client to prevent lags.
    //  You can use hints from comment below, or implement your own approach

    //........................................................................
    int sockfd;
    struct sockaddr_in serv_addr;
    struct sockaddr client_address;

    sockfd = socket(AF_INET, SOCK_STREAM,0);

    if(sockfd < 0) {
        std::cout << "Socket opening error:(";
        return -1;
    }

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;



    while((bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 && port <= MAX_PORT)) {
        serv_addr.sin_port = htons(++port);
    }
    std::cout << "current port:" << port << '\n';

    if(port > MAX_PORT) {
        return -1;
    }

    listen(sockfd, 5);
    //............................................................................................
    //^prepared to connections on our port^

    // socklen_t clilen = sizeof(client_address);



    std::cout << "connection accepted\n";


    startBrowser();

    socklen_t clilen = sizeof(client_address);
    while(!needStop) {
        int new_socket = accept(sockfd, (struct sockaddr*)&serv_addr, &clilen);
        if(new_socket < 0) {
            std::cout << "acception error:(";
            return -2;
        }
        int cliId = ++clientsCount;
        std::cout << "Accept ok for client " << cliId << std::endl;

        std::thread client(clientThread, new_socket, cliId);
        client.detach();
    }

    close(sockfd);

    return 0;
}