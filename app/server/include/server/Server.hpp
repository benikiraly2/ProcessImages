#pragma once

#include <cstdint>
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>

#include "clients/Client.hpp"
#include "sockets/Socket.hpp"
#include "workers/Worker.hpp"
#include "Timer.hpp"

namespace n_server
{

class ServerWrapper;

class Server
{
public:
    ~Server();
    void start();
private:
    friend ServerWrapper;
    Server();

    void clientListener() noexcept(false);
    void clientReader() noexcept(false);
    void clientWriter() noexcept(false);
    void close();

    bool isStarted{true};
    n_socket::Socket serverSocket;

    std::vector<n_workers::Worker> workers;
    std::vector<std::thread> workerThreads;
    std::vector<timer::Timer> clientTimers;
    UserData users;
};

}
