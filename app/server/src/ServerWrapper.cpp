#include <signal.h>

#include "server/Server.hpp"
#include "server/ServerWrapper.hpp"

namespace n_server
{

std::unique_ptr<Server> ServerWrapper::server;

ServerWrapper::ServerWrapper()
{
    signal(SIGINT, ServerWrapper::interrupt);
}

Server& ServerWrapper::instance()
{
    if (not server)
    {
        ServerWrapper::server = std::unique_ptr<Server>(new Server);
    }
    return *server;
}

void ServerWrapper::interrupt(int signal)
{
    if (signal == SIGINT)
        ServerWrapper::server->close();
}

}