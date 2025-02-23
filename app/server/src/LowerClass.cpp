#include "server/LowerClass.hpp"
#include "server/Distributor.hpp"

LowerClass::LowerClass(Distributor& distributor) : distributor{distributor} {}

void LowerClass::onMessage(const boost_messages::SetupRequest &setupRequest)
{
    std::cout << "LowerClass onMessage SetupRequest: " << setupRequest << "\n";
}


