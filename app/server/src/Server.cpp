#include <exception>
#include <functional>
#include <iostream>

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
{}

Server::~Server()
{
    close();
}

void Server::start()
{
    std::cout << "Server started\n";
    auto clientListenerCallback = [this](){clientListener();};
    auto clientReaderCallback = [this](){clientReader();};
    auto clientWriterCallback = [this](){clientWriter();};

    clientTimers.emplace_back(timer::Timer(clientListenerCallback, 10));
    clientTimers.emplace_back(timer::Timer(clientReaderCallback, 50));
    clientTimers.emplace_back(timer::Timer(clientWriterCallback, 100));

    for(timer::Timer& timer : clientTimers)
    {
        timer.start();
    }

    workers.reserve(NUM_WORKERS);
    for (int worker_nr = 0; worker_nr < NUM_WORKERS; worker_nr++)
    {
        workers.emplace_back(n_workers::Worker(users));
        workerThreads.emplace_back(std::thread(&n_workers::Worker::start, &workers[worker_nr]));
    }

    auto controlWorkerDistributionCallback = [this](){controlClientTimer();};
    auto controlClientTimerCallback = [this](){controlWorkerDistribution();};
    controlTimers.emplace_back(timer::Timer(controlClientTimerCallback, 1000));
    controlTimers.emplace_back(timer::Timer(controlWorkerDistributionCallback, 100));

    for(timer::Timer& timer : controlTimers)
    {
        timer.start();
    }

    isStarted = true;

    for (std::thread& thread : workerThreads)
    {
        thread.join();
    }

    workerThreads.clear();
    std::cout << "Server ended\n";
}

void Server::clientListener()
{
    if (not isStarted)
    {
        return;
    }

    std::cout << "Triggered clientListener\n";
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

void Server::clientReader()
{
    if (not isStarted)
    {
        return;
    }
    /*
        read from each existing client
        max bytes read = 8192, where:
            result[0] = message type (1 byte)
            result[1] = number of bytes part 1 ( << 8) ---> 0xff00
            result[2] = number of bytes part 2 ---> 0x00ff

            Leaves actual maximum data bytes to read = 8189

        Convert result[0] to actual Message, see Messages.hpp
    */
    std::vector<std::uint8_t> buffer;
    for (auto const& [clientFD, client] : users)
    {
        std::uint8_t message = 0;
        std::uint16_t dataRead = 0;
        // serverSocket.read(data, clientFD, message, dataRead);
        serverSocket.read(buffer, clientFD);

        /*
            Insert in a FIFO struct and let another server thread process it
            this thread will continue reading from clients
        */
        // data.append(buffer.cbegin() + 3, buffer.cend());

        buffer.clear();
    }
}

void Server::clientWriter()
{
    if (not isStarted)
    {
        return;
    }
    // for (auto const& [clientFD, client] : users)
    // {
    //     const n_clients::ClientDataSet& readyDataSet = client->getDataSet();
    //     if (not readyDataSet.empty())
    //     {
    //         std::cout << "Sending data to: " << clientFD << "\n";
    //         for (auto revIt = readyDataSet.rbegin(); revIt != readyDataSet.rend(); revIt++)
    //         {
    //             serverSocket.write(clientFD, revIt->data);
    //         }
    //         client->readyNextDataSet();
    //     }
    // }
}

void Server::controlClientTimer()
{
}


void Server::controlWorkerDistribution()
{
    static std::uint8_t workerIndex = 0;

    while (not dataQueue.empty())
    {
        const std::string& data = dataQueue.front();

        // workers[workerIndex++].add(n_clients::ClientData(data));
        // workerIndex = workerIndex % NUM_WORKERS;

        dataQueue.pop();
    }
}

void Server::close()
{
    if (isStarted)
    {
        clientTimers.clear();
        isStarted = false;
        serverSocket.close();
        workers.clear();
        users.clear();
    }
}

}