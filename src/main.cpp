#include <boost/gil/extension/io/jpeg.hpp>
#include <iostream>
#include <thread>
#include <sstream>
#include"server.h"

using namespace boost::gil;


int main() {

    std::string inputFileName("/home/oleksandr/Dithering/assets/original.jpg");
    std::string outputFileName("/home/oleksandr/Dithering/outputs/dithered.jpg");

    std::thread mainServerThread(mainServerThreadRoutine);

    mainServerThread.join();

    //colorToGreyScale(inputFileName, outputFileName);

    return EXIT_FAILURE;
}

