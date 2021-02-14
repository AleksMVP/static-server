cmake_minimum_required(VERSION 3.15)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include")
link_directories("/usr/lib")
link_directories("/usr/local/lib")

find_package(Boost REQUIRED system)

add_executable(MyProject main.cpp Server.cpp LoggingHandler.cpp HTTPHandler.cpp Request.cpp Response.cpp Client.cpp ResponseBuilder.cpp)
target_link_libraries (MyProject -lboost_coroutine -lboost_chrono -lboost_thread-mt -lboost_system)
