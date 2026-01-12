#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>


int main()
{
    //1. 创建socket
    //AF_INET: 使用IPV4，SOCK_STREAM::使用TCP流式传输
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd == 1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }

    //2. 准备地址结构体
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//anyway 允许任何IP链接
    address.sin_port = htons(8080);

    //绑定端口
    if(bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0)
    {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    //监听（开机等待）
    //3 代表等待队列的长度
    if(listen(server_fd,3)<0)
    {
        std::cerr << "Listern failed" << std::endl;
        return -1;
    }

    std::cout<< "服务器正在监听 8080 端口" << std::endl;

    // 4. 接受连接（阻塞等待直到有电话打进来
    int addrlen = sizeof(address);
    //accept会卡住程序，直到有客户端连接
    int new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t*)&addrlen);
    if(new_socket <0)
    {
        std::cerr<< "Accept faild" << std::endl;
        return -1;
    }

    std::cout<< "客户端连接成功" <<std::endl;

    //5.循环读取数据
    char buffer[1024] = {0};
    while(true)
    {
        memset(buffer,0,sizeof(buffer));
        //read也会阻塞，直到客户端发数据
        int valread = read(new_socket,buffer,1024);

        if(valread <=0)//客户端断开连接出错
        {
            std::cout<< "客户端断开连接"<< std::endl;
            break;
        }

        std::cout<<"收消息"<<buffer<<std::endl;
        //发回同样的消息(Echo)
        send(new_socket,buffer,valread,0);
    }
    close(new_socket);
    close(server_fd);
    return 0;


}