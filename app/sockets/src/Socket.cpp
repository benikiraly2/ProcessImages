#include <cstdint>
#include <iostream>

#include "exceptions/Exceptions.hpp"
#include "sockets/Socket.hpp"

namespace n_socket
{

Socket::Socket()
{
    addressLength = sizeof(address);
    std::cout << "Constructing socket\n";
}

Socket::~Socket()
{
    std::cout << "Destructing socket\n";
    close();
}

void Socket::start(const int port, const int backlog_max)
{
    if ((socketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw custom_exceptions::SocketCreationException();
    }
 
    if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        throw custom_exceptions::SocketOptionSetException();
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketFD, (struct sockaddr*)&address, addressLength) < 0)
    {
        throw custom_exceptions::SocketAttachException();
    }

    if (listen(socketFD, backlog_max) < 0)
    {
        throw custom_exceptions::SocketListenException();
    }

    isStarted = true;
    std::cout << "Socket succesfully started\n";
}

void Socket::close()
{
    if (isStarted)
    {
        ::shutdown(socketFD, SHUT_RD);
        ::close(socketFD);
        isStarted = false;
    }
}

int Socket::accept()
{
    int connection;

    if ((connection = ::accept(socketFD, (struct sockaddr*)&address, &addressLength)) < 0)
    {
        throw custom_exceptions::SocketAcceptException();
    }

    return connection;
}

void Socket::read(std::vector<std::uint8_t>& buffer, const int& connection)
{
    int bytesReceived = ::recv(connection, &buffer[0], MAX_BYTES_READ, 0);
    buffer.resize(bytesReceived);
}

void Socket::write(const int& connection, std::string data)
{
    auto bytesSent = ::send(connection, data.c_str(), data.size(), 0);
}

}