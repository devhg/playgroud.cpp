//
// Created by devhg on 2021/9/10.
//

/**
* TCP服务器通信基本流程
* client 简单代码
* 2021.09.10
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 3000
#define SEND_DATA "hello world"

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr = {};
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_addr.sin_port        = htons(SERVER_PORT);

    if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        std::cout << "connect socket error." << std::endl;
        return -1;
    }

    int ret = send(client_fd, SEND_DATA, strlen(SEND_DATA), 0);
    if (ret != strlen(SEND_DATA)) {
        std::cout << "send data error." << std::endl;
        return -1;
    }

    char recv_buff[32] = {0};
    ret = recv(client_fd, recv_buff, 32, 0);
    if (ret > 0) {
        std::cout << "recv data successfully, data: " << recv_buff << std::endl;
    } else {
        std::cout << "recv data error, data: " << recv_buff << std::endl;
    }

    while (true) {
        sleep(3);
    }
    return 0;
}
