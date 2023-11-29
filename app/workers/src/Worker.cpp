#include "workers/Worker.hpp"
#include <iostream>

namespace n_workers
{

Worker::Worker(const UserData& users) :
    users(users)
{
    std::cout << "Worker construction\n";
}

Worker::~Worker()
{
    std::cout << "Worker destruction\n";
    isStarted = false;
}

void Worker::start()
{
    std::cout << "Worker thread started\n";
    while (isStarted)
    {

    }
    std::cout << "Worker thread ended\n";
}

}