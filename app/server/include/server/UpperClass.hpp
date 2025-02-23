#pragma once
#include "server/BOOSTMessages.hpp"

class Distributor;

class UpperClass
{
public:
    UpperClass(Distributor&);

    void start();
    void receive(const boost_messages::LMsg& msg);
private:
    void onMessage(const boost_messages::SetupResponse& setupResponse);
    Distributor& distributor;
    CellIds cellIds;
};
