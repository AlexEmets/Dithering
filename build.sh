#!/bin/bash
mkdir -p build && cd build
cmake ..
cmake --build .
#g++ -Wall -Wextra -pedantic -pthread -o Dithering ../src/main.cpp ../src/server.cpp ../src/client.cpp -ljpeg
./Dithering
