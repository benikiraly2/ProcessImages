#pragma once
#include "server/BOOSTMessages.hpp"

class Distributor;

class LowerClass
{
public:
    LowerClass(Distributor&);
    void receive(const boost_messages::UMsg& msg);
private:
    void onMessage(const boost_messages::SetupRequest&);
    Distributor& distributor;
    CellIds cellIds;
};
