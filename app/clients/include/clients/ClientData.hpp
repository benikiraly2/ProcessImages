#pragma once

#include <set>
#include <string>

namespace n_clients
{

using ClientFD = int;
using TransactionID = int;

struct ClientData
{
    std::string data;
    TransactionID transactionId;
};

struct ClientDataComparator
{
    inline bool operator()(ClientData left, ClientData right) const
    {
        return left.transactionId > right.transactionId;
    }
};

using ClientDataSet = std::set<ClientData, ClientDataComparator>;
} // n_clients