cmake_minimum_required(VERSION 3.17)
project(serial_test)

set(CMAKE_CXX_STANDARD 14)
find_package(Poco REQUIRED Foundation)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads REQUIRED)

add_executable(serial_test main.cpp SerialCOM.cpp SerialCOM.hpp)
include_directories(Boost::boost)
target_link_libraries(serial_test PocoFoundation Boost::system Boost::thread)