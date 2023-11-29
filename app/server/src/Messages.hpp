#pragma once

#include <cstdint>

namespace messages
{

enum class MessageIds : std::uint8_t
{
    // ========== CLIENT ===========

    CONNECT = 0,
    PLAN,
    INFO,
    DATA,

    // ========== ADMIN ===========
};

}