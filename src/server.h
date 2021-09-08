//
// Created by oleksandr on 05/09/2021.
//

#ifndef DITHERING_SERVER_H
#define DITHERING_SERVER_H

int mainServerThreadRoutine();

void startBrowser();

int clientThread(int newsockfd, int clientId);

std::pair<std::string, std::string> processRequest(const std::string &requestData);

std::string getRequestData(std::string data);

std::string getHttpResponse(const std::string &textResponse, const std::string &contentType);

#endif //DITHERING_SERVER_H
