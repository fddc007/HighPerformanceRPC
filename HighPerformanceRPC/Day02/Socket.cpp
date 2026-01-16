#include"Socket.h"
#include"InetAddress.h"
#include"util.h"
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>

Socket::Socket():fd(-1)
{
    fd = socket(AF_INET,SOCK_STREAM,0);
    ErrorIf(fd==-1,"socket create error");
}

Socket::Socket(int _fd):fd(_fd)
{
    ErrorIf(fd == -1,"socket create error");
}

Socket::~Socket()
{
    if(fd!=-1)
    {
        close(fd);
    }
}

void Socket::bind(InetAddress* addr)
{
    //设置端口复用（关键优化：允许服务器重启后立即使用同一端口）
    int opt = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    int ret = ::bind(fd,(struct sockaddr*)&addr->addr,addr->addr_len);
    ErrorIf(ret==-1,"socket bind error");
}

void Socket::listen()
{
    int ret = ::listen(fd,SOMAXCONN);
    ErrorIf(ret == -1,"socket listen error");
}

int Socket::accept(InetAddress *addr) {
    int clnt_fd = ::accept(fd, (struct sockaddr*)&addr->addr, &addr->addr_len);
    ErrorIf(clnt_fd == -1, "socket accept error");
    return clnt_fd;
}

int Socket::getFd()
{
    return fd;
}