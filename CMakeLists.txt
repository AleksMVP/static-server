cmake_minimum_required(VERSION 3.15)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

include_directories("/usr/local/include")
include_directories("include")
link_directories("/usr/lib")
link_directories("/usr/local/lib")

find_package(Boost REQUIRED system)

add_executable(MyProject src/main.cpp src/Response.cpp src/Request.cpp src/Client.cpp src/Utils.cpp)
target_link_libraries (MyProject -lboost_coroutine -lboost_chrono -lboost_thread-mt -lboost_system)
