#include<iostream>
#include"Socket.h"
#include"InetAddress.h"
#include<unistd.h>
#include<cstring>

int main()
{
    //1.创建socket并绑定端口（RAII自动管理）
    Socket *serv_sock = new Socket();
    InetAddress* serv_addr = new InetAddress("127.0.0.1",8888);

    serv_sock->bind(serv_addr);
    serv_sock->listen();

    std::cout<<"Server start success! Listening on port 8888..."<<std::endl;

    //2. 接受链接（在这之前依旧是阻塞，只能链接一个）
    InetAddress* clnt_addr = new InetAddress();
    int clnt_fd = serv_sock->accept(clnt_addr);

    std::cout<<"New client connected,fd:"<<clnt_fd<<std::endl;


    //3.Echo逻辑
    while(true)
    {
        char buf[1024];
        memset(buf,0,sizeof(buf));
        ssize_t read_bytes = read(clnt_fd,buf,sizeof(buf));
        if(read_bytes>0)
        {
            std::cout<<"Message:"<<buf<<std::endl;
            write(clnt_fd,buf,sizeof(buf));
        }
        else
        {
            std::cout<<"Client disconnect"<<std::endl;
            break;
        }
    }

    //4.清理资源
    //当serv_sock 被delete时，~Socket（）会自动执行close（fd）
    delete serv_addr;
    delete clnt_addr;
    delete serv_sock;
    return 0;
}