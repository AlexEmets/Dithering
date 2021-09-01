cmake_minimum_required(VERSION 3.14)

project(Dithering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic -lpthread")

find_package(Boost 1.73 COMPONENTS program_options REQUIRED)

set(SOURCE_LIST
    src/main.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCE_LIST}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE include/)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})
