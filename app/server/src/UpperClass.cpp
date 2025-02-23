#include "server/UpperClass.hpp"
#include "server/Distributor.hpp"

UpperClass::UpperClass(Distributor& distributor) : distributor{distributor} {}

void UpperClass::start()
{
    cellIds = {5, 10, 15};
    
}


void UpperClass::onMessage(const boost_messages::SetupResponse &setupResponse)
{
    std::cout << "UpperClass onMessage SetupResponse: " << setupResponse << "\n";
}


