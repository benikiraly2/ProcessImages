#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

using CellIds = std::vector<std::uint32_t>;
using Payload = std::vector<std::uint8_t>;

namespace boost_messages
{

enum class MessageIds : std::uint8_t
{
    SetupRequest = 0,
    SetupResponse,
    ModifRequired,
    ModifRequest,
    ModifResp,
    ReleaseRequest,
    ReleaseComplete,
    ErrorInd
};

enum class MessageStatus : std::uint8_t
{
    OK,
    NOT_OK
};

enum class ReleaseCause : std::uint8_t
{
    Cause1,
    Cause2
};

std::ostream& operator<<(std::ostream& os, const MessageIds msgId)
{
    switch (msgId)
    {
        case MessageIds::SetupRequest:
            os << "SetupRequest"; break;
        case MessageIds::SetupResponse:
            os << "SetupResponse"; break;
        case MessageIds::ModifRequired:
            os << "ModifRequired"; break;
        case MessageIds::ModifRequest:
            os << "ModifRequest"; break;
        case MessageIds::ModifResp:
            os << "ModifResp"; break;
        case MessageIds::ReleaseRequest:
            os << "ReleaseRequest"; break;
        case MessageIds::ReleaseComplete:
            os << "ReleaseComplete"; break;
        case MessageIds::ErrorInd:
            os << "ErrorInd"; break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const MessageStatus status)
{
    switch (status)
    {
        case MessageStatus::OK:
            os << "OK"; break;
        case MessageStatus::NOT_OK:
            os << "NOT_OK"; break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const ReleaseCause cause)
{
    switch (cause)
    {
        case ReleaseCause::Cause1:
            os << "Cause1"; break;
        case ReleaseCause::Cause2:
            os << "Cause2"; break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CellIds& cellIds)
{
    os << "CellIds { ";

    for (auto it = cellIds.begin(); it != cellIds.end(); it++)
    {
        os << *it;
        if ((it + 1) != cellIds.end())
        {
            os << ", ";
        }
    }

    os << " }";
    return os;
}

namespace
{
    struct TID
    {
        uint16_t transactionId;
    };

    struct UEID
    {
        uint16_t ueId;
    };
} // namespace

struct SetupRequest : public TID, public UEID
{
    friend std::ostream& operator<<(std::ostream& os, const SetupRequest& response)
    {
        os << "SetupResponse { " << response.transactionId << ", " << response.ueId << ", " << response.cellIds << " }";
        return os;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & MessageIds::SetupRequest & transactionId & ueId & cellIds;
    }

    CellIds cellIds;
};

struct SetupResponse : public TID, public UEID
{
    friend std::ostream& operator<<(std::ostream& os, const SetupResponse& response)
    {
        os << "SetupResponse { " << response.transactionId << ", " << response.ueId << ", " << response.status << " }";
        return os;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & MessageIds::SetupResponse & transactionId & ueId & status;
    }

    static 

    boost_messages::MessageStatus status;
};

// struct ModificationRequired : public TID, public UEID
// {
//     CellIds cellIdsToAdd;
//     CellIds cellIdsToRemove;
// };

// struct ModificationRequest : public TID, public UEID
// {
//     CellIds cellIdsToAdd;
//     CellIds cellIdsToRemove;
// };

// struct ModificationResponse: public TID, public UEID
// {
//     boost_messages::MessageStatus status;
// };

// struct ReleaseRequest : public TID, public UEID
// {
//     boost_messages::ReleaseCause cause;
// };

// struct ReleaseComplete : public TID, public UEID
// {
//     boost_messages::MessageStatus status;
// };

// struct ErrorIndication : public TID, public UEID
// {
//     std::string incident;
// };

struct UMsg
{
    Payload message;
};

struct LMsg
{
    Payload message;
};

}