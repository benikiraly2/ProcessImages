#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>

#include "exceptions/Exceptions.hpp"
#include "Messages.hpp"
#include "server/Server.hpp"

namespace
{
#define C_PORT 7836
#define A_PORT 46758
#define BACKLOG_MAX 200
constexpr std::uint8_t NUM_WORKERS = 6;
}

namespace n_server
{

Server::Server()
{
    std::cout << "Constructing server\n";
}

Server::~Server()
{
    std::cout << "Destructing server\n";
    close();
}

void Server::start()
{
    std::cout << "Server start started\n";

    clientThreads.emplace_back(std::thread(&Server::startClientListener, this));
    clientThreads.emplace_back(std::thread(&Server::startClientReader, this));
    clientThreads.emplace_back(std::thread(&Server::startClientWriter, this));

    workers.reserve(NUM_WORKERS);
    for (int worker_nr = 0; worker_nr < NUM_WORKERS; worker_nr++)
    {
        workers.emplace_back(n_workers::Worker(users));
        workerThreads.emplace_back(std::thread(&n_workers::Worker::start, &workers[worker_nr]));
    }

    for (std::thread& thread : clientThreads)
    {
        thread.join();
    }

    for (std::thread& thread : workerThreads)
    {
        thread.join();
    }
    workerThreads.clear();
    clientThreads.clear();
    std::cout << "Server start ended\n";
}

void Server::startClientListener()
{
    std::cout << "Server startClientListener thread started\n";
    while (isStarted)
    {
        std::shared_ptr<n_clients::ClientFD> clientFD = std::make_shared<n_clients::ClientFD>(0);
        std::shared_ptr<n_clients::Client> client = std::make_shared<n_clients::Client>(clientFD);
        try
        {
            serverSocket.start(C_PORT, BACKLOG_MAX);
            *clientFD = serverSocket.accept();

            users.insert(std::make_pair(*clientFD, client));
            std::cout << "New client connected, id: " << clientFD << "\n";
        }
        catch (const custom_exceptions::CustomException& e)
        {
            std::cout << "CUSTOM EXCEPTION: " << e.what() << '\n';
            isStarted = false;
        }
        catch(const std::exception& e)
        {
            std::cout << "BAD EXCEPTION " << e.what() << '\n';
            isStarted = false;
            throw std::bad_exception();
        }
    }
    std::cout << "Server startClientListener thread ended\n";
}

void Server::startClientReader()
{
    std::cout << "Server startClientReader thread started\n";
    while (isStarted)
    {

    }
    std::cout << "Server startClientReader thread ended\n";
}

void Server::startClientWriter()
{
    std::cout << "Server startClientWriter thread started\n";
    while (isStarted)
    {
        for (auto const& [clientFD, client] : users)
        {
            const n_clients::ClientDataSet& readyDataSet = client->getDataSet();
            if (not readyDataSet.empty())
            {
                std::cout << "Sending data to: " << clientFD << "\n";
                for (auto revIt = readyDataSet.rbegin(); revIt != readyDataSet.rend(); revIt++)
                {
                    serverSocket.write(clientFD, revIt->data);
                }
                client->readyNextDataSet();
            }
        }
    }
    std::cout << "Server startClientWriter thread ended\n";
}

void Server::close()
{
    if (isStarted)
    {
        isStarted = false;
        serverSocket.close();
        workers.clear();
        users.clear();
    }
}

}