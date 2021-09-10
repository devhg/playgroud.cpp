//
// Created by devhg on 2021/9/10.
//

/**
* TCP服务器通信基本流程
* server 简单代码
* 2021.09.10
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    struct sockaddr_in bind_addr = {};
    bind_addr.sin_family      = AF_INET;
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port        = htons(3000);

    if (bind(listen_fd, (struct sockaddr *) &bind_addr, sizeof(bind_addr)) == -1) {
        std::cout << "bind listen socket error." << std::endl;
        return -1;
    }

    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cout << "listen error." << std::endl;
        return -1;
    }

    // 记录所有客户端连接的容器
    std::vector<int> client_fds;
    while (true) {
        struct sockaddr_in client_addr     = {};
        socklen_t          client_addr_len = sizeof(client_addr);

        int client_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd != -1) {
            char recv_buff[32] = {0};

            int n = recv(client_fd, recv_buff, 32, 0);
            if (n > 0) {
                std::cout << "recv data from server, data: " << recv_buff << std::endl;
                n = send(client_fd, recv_buff, strlen(recv_buff), 0);
                if (n != strlen(recv_buff))
                    std::cout << "send data error." << std::endl;

                std::cout << "send data to server successfully, data: "
                          << recv_buff << std::endl;
            }
        } else {
            std::cout << "recv data error." << std::endl;
        }
        client_fds.push_back(client_fd);
    }

    close(listen_fd);
    return 0;
}
