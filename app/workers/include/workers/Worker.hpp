#pragma once

#include <unordered_map>

#include "clients/Client.hpp"

namespace n_workers
{

class Worker
{
public:
    Worker(const UserData&);
    ~Worker();
    void start();
private:
    const UserData& users;
    bool isStarted = true;
};

}