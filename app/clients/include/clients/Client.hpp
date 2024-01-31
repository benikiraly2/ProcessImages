#pragma once

#include <memory>
#include <ostream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <set>

#include "clients/ClientData.hpp"
#include "clients/IClient.hpp"

namespace n_clients
{

class Client : public IClient
{
public:
    Client(const std::shared_ptr<ClientFD> clientFD);
    Client& operator=(const Client&);
    ~Client();
    friend std::ostream& operator<<(std::ostream& os, const Client& client);

    const ClientFD& getFD() const override { return *clientFD; }
    int getTotalTransactions() const override { return totalTransactions; }
    void setTotalTransactions(int totalTransactions) override { this->totalTransactions = totalTransactions; }
    
    const ClientDataSet& getDataSet() const override;
    void insertProcessedData(ClientData clientData) override;
    void readyNextDataSet() override;

private:
    std::mutex rwMutex; // Read Write Mutual Exclusive flag

    std::shared_ptr<ClientFD> clientFD;
    int processedTransactions;
    int totalTransactions;
    ClientDataSet dataSet;
};

}

using UserData = std::unordered_map<n_clients::ClientFD, std::shared_ptr<n_clients::Client>>;