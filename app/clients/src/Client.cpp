#include <unistd.h>

#include "clients/Client.hpp"

namespace n_clients
{

bool ClientDataComparator(ClientData left, ClientData right)
{
    return left.transactionId > right.transactionId;
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
    int i = 0;
    os << "Client (" << client.clientFD << ") dataSet: { ";
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
    , dataSet(ClientDataComparator)
{}

Client::~Client()
{
    close(*clientFD);
}

void Client::insertProcessedData(ClientData clientData)
{
    std::lock_guard<std::mutex> guard(rwMutex);
    dataSet.insert(clientData);
}

ClientDataSet Client::getReadyDataSet()
{
    static int previousTransactionId = -1;
    ClientDataSet readyDataSet;
    std::lock_guard<std::mutex> guard(rwMutex);
    auto dataIt = dataSet.rbegin();
    for (; dataIt != dataSet.rend() && dataIt->transactionId == previousTransactionId + 1; dataIt++)
    {
        readyDataSet.insert(*dataIt);
        previousTransactionId = dataIt->transactionId;
    }

    for (auto eraseIt = dataSet.rbegin(); eraseIt != dataIt; eraseIt++)
    {
        dataSet.erase(*eraseIt);
    }

    return readyDataSet;
}

const ClientDataSet& Client::getDataSet() const
{
    return dataSet;
}

void Client::clearDataSet()
{
    dataSet.clear();
}

}