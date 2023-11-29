#include "exceptions/Exceptions.hpp"

namespace custom_exceptions
{

const char* SocketAcceptException::what() const
{
    return "An error occured during accepting connection!";
}

const char* SocketAttachException::what() const
{
    return "Could not bind/attach socket to port!";
}

const char* SocketCreationException::what() const
{
    return "Could not create socket!";
}

const char* SocketListenException::what() const
{
    return "Could not set listen backlog value on socket!";
}

const char* SocketOptionSetException::what() const
{
    return "Could not set socket options!";
}

}