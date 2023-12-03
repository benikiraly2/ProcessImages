#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

namespace n_socket
{

namespace
{
#define BACKLOG_MAX 200
}

class Socket
{
public:
    Socket();
    ~Socket();
    void start(const int port, const int backlog_max = BACKLOG_MAX) noexcept(false);
    void close();
    int accept() noexcept(false);
    void read(const int& connection);
    void write(const int& connection, std::string data);
private:
    bool isStarted = false;
    int socketFD;
    int opt = 1;
    struct sockaddr_in address;
    socklen_t addressLength;
};

}
