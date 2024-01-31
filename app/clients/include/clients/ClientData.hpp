#pragma once

#include <cstdint>
#include <set>
#include <string>

namespace n_clients
{

using ClientFD = std::uint32_t;
using TransactionID = std::uint32_t;

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