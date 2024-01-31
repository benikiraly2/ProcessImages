#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <sstream>

#include "exceptions/Exceptions.hpp"

namespace n_exceptions_test
{

using namespace ::testing;

class ExceptionsTest : public Test
{
};

TEST_F(ExceptionsTest, testSocketAcceptException)
{
    try {
        throw custom_exceptions::SocketAcceptException();
    } catch (const custom_exceptions::CustomException& e) {
        EXPECT_STREQ("An error occured during accepting connection!", e.what());
    }
}

TEST_F(ExceptionsTest, SocketAttachException)
{
    try {
        throw custom_exceptions::SocketAttachException();
    } catch (const custom_exceptions::CustomException& e) {
        EXPECT_STREQ("Could not bind/attach socket to port!", e.what());
    }
}

TEST_F(ExceptionsTest, SocketCreationException)
{
    try {
        throw custom_exceptions::SocketCreationException();
    } catch (const custom_exceptions::CustomException& e) {
        EXPECT_STREQ("Could not create socket!", e.what());
    }
}

TEST_F(ExceptionsTest, SocketListenException)
{
    try {
        throw custom_exceptions::SocketListenException();
    } catch (const custom_exceptions::CustomException& e) {
        EXPECT_STREQ("Could not set listen backlog value on socket!", e.what());
    }
}

TEST_F(ExceptionsTest, SocketOptionSetException)
{
    try {
        throw custom_exceptions::SocketOptionSetException();
    } catch (const custom_exceptions::CustomException& e) {
        EXPECT_STREQ("Could not set socket options!", e.what());
    }
}

}