#include "server/Distributor.hpp"
#include "server/LowerClass.hpp"
#include "server/UpperClass.hpp"

Distributor::Distributor()
{
    upperClass = std::make_unique<UpperClass>(*this);
    lowerClass = std::make_unique<LowerClass>(*this);
}

void Distributor::send(const boost_messages::UMsg& msg)
{
    // serialize msgId and combine with msg.message to create a single payload
}

void Distributor::send(const boost_messages::LMsg& msg)
{
    // serialize msgId and combine with msg.message to create a single payload
}
