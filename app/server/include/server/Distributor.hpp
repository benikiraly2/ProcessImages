#pragma once

#include <memory>

#include "server/BOOSTMessages.hpp"

class UpperClass;
class LowerClass;

class Distributor
{
public:
    Distributor();
    void send(const boost_messages::UMsg& msg);
    void send(const boost_messages::LMsg& msg);
private:
    std::unique_ptr<UpperClass> upperClass;
    std::unique_ptr<LowerClass> lowerClass;
};


