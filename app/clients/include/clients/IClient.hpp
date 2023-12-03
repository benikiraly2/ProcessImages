#pragma once

#include <set>
#include <string>

#include "clients/ClientData.hpp"

namespace n_clients
{

class IClient
{
    virtual const ClientFD& getFD() const = 0;
    virtual int getTotalTransactions() = 0;
    virtual void setTotalTransactions(int totalTransactions) = 0;
    
    virtual const ClientDataSet& getDataSet() const = 0;
    virtual void insertProcessedData(ClientData clientData) = 0;
    virtual void readyNextDataSet() = 0;
};

}