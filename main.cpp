
#include <iostream>
#include <memory>
#include <string>

#include "server/Server.hpp"
#include "server/ServerWrapper.hpp"

int main()
{
    n_server::ServerWrapper serverWrapper;
    n_server::Server& server = serverWrapper.instance();

    std::thread serverThread(&n_server::Server::start, &server);
    serverThread.join();
    return 0;
}