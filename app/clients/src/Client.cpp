#include <unistd.h>

#include "clients/Client.hpp"
#include <iostream>

namespace n_clients
{

std::ostream& operator<<(std::ostream& os, const Client& client)
{
    int i = 0;
    os << "Client (" << *client.clientFD << ") dataSet: { ";
    for (const ClientData& element : client.dataSet)
    {
        os << element.transactionId;
        if (i < client.dataSet.size() - 1)
        {
            os << ", ";
        }
        i++;
    }
    os << " }\n";
    return os;
}

Client::Client(const std::shared_ptr<ClientFD> clientFD) :
    clientFD(clientFD)
    , processedTransactions{0}
    , totalTransactions{0}
{}

Client& Client::operator=(const Client& client)
{
    clientFD = client.clientFD;
    processedTransactions = client.processedTransactions;
    totalTransactions = client.totalTransactions;
    dataSet = client.dataSet;
    return *this;
}

Client::~Client()
{
    close(*clientFD);
}

void Client::insertProcessedData(ClientData clientData)
{
    std::lock_guard<std::mutex> guard(rwMutex);
    dataSet.insert(clientData);
}

const ClientDataSet& Client::getDataSet() const
{
    return dataSet;
}

void Client::readyNextDataSet()
{
    dataSet.clear();
}

}