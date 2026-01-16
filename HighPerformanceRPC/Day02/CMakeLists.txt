cmake_minimum_required(VERSION 3.10)
project(MyRPC)

#设置C++标准
set(CMAKE_CXX_STANDARD 11)
#开始调试模式（-g) 和 所有警告（—Wall）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

include_directories(.)

# 告诉Cmake：执行文件叫server
# 它由后面5个源文件组成
add_executable(
    server
    util.cpp
    InetAddress.cpp
    Socket.cpp
    server.cpp
)