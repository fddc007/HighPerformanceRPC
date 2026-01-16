#pragma once

class InetAddress;//前置声明

class Socket
{
public:
    Socket();
    Socket(int _fd);
    ~Socket();//close(fd)

    void bind(InetAddress *addr);
    void listen();
    int accept(InetAddress* addr);
    int getFd();
private:
    int fd;//文件描述符
};