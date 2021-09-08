cmake_minimum_required(VERSION 3.14)

project(Dithering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread -ljpeg")

find_package(Boost 1.71 COMPONENTS program_options REQUIRED)

set(SOURCE_LIST
        src/main.cpp

        src/server.h
        src/server.cpp

        src/image_processing.h
        src/image_processing.cpp

        )

add_executable(${PROJECT_NAME}
        ${SOURCE_LIST}
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE include/)

target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES})
