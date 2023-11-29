#pragma once

#include <memory>
#include <ostream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <set>

namespace n_clients
{

using ClientFD = int;

struct ClientData
{
    std::string data;
    int transactionId;
};

bool ClientDataComparator(ClientData left, ClientData right);
using ClientDataSet = std::set<n_clients::ClientData, decltype(n_clients::ClientDataComparator)*>;

class Client
{
public:
    Client(const std::shared_ptr<ClientFD> clientFD);
    ~Client();
    friend std::ostream& operator<<(std::ostream& os, const Client& client);

    const ClientFD& getFD() const { return *clientFD; }
    int getTotalTransactions() { return totalTransactions; }
    void setTotalTransactions(int totalTransactions) { this->totalTransactions = totalTransactions; }
    
    ClientDataSet getReadyDataSet();
    const ClientDataSet& getDataSet() const;
    void insertProcessedData(ClientData clientData);
    void clearDataSet();

    std::mutex rwMutex;
private:

    const std::shared_ptr<ClientFD> clientFD;
    int processedTransactions;
    int totalTransactions;
    ClientDataSet dataSet;
};

}

using UserData = std::unordered_map<n_clients::ClientFD, std::shared_ptr<n_clients::Client>>;