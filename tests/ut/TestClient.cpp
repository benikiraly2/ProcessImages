#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <sstream>

#include "clients/Client.hpp"
#include "clients/ClientData.hpp"

namespace
{

constexpr n_clients::ClientFD expectedFD = 15;

}

namespace n_clients_test
{

using namespace ::testing;

class ClientTest : public Test
{
public:
    void SetUp() override
    {
        expectedClientFD = std::make_shared<n_clients::ClientFD>(expectedFD);
        expectedClientDataSet = {{"test", 2}, {"asd", 7}, {"dsa", 3}, {"press F", 0}};
        expectedTransactionIdOrder = {7, 3, 2, 0};
        sut = std::make_shared<n_clients::Client>(expectedClientFD);
    }

    std::shared_ptr<n_clients::ClientFD> expectedClientFD;
    n_clients::ClientDataSet expectedClientDataSet;
    std::vector<n_clients::TransactionID> expectedTransactionIdOrder;

    std::shared_ptr<n_clients::Client> sut;
};

TEST_F(ClientTest, testFD)
{
    ASSERT_EQ(sut->getFD(), 15);
}

TEST_F(ClientTest, testClientDataSet)
{
    auto orderIt = expectedTransactionIdOrder.begin();
    auto dataSetIt = expectedClientDataSet.begin();

    for (std::size_t total = 0; total < expectedTransactionIdOrder.size(); total++)
    {
        ASSERT_EQ(*orderIt, dataSetIt->transactionId);
        orderIt++;
        dataSetIt++;
    }
}

TEST_F(ClientTest, testClientPrintWithInsert)
{
    for (auto clientData : expectedClientDataSet)
    {
        sut->insertProcessedData(clientData);
    }

    std::string expectedResult = "Client (15) dataSet: { 7, 3, 2, 0 }\n";

    std::ostringstream result;
    result << *sut;

    ASSERT_EQ(expectedResult, result.str());
}

TEST_F(ClientTest, testGetDataSetWithInsert)
{
    for (auto clientData : expectedClientDataSet)
    {
        sut->insertProcessedData(clientData);
    }

    const n_clients::ClientDataSet& sutDataSet = sut->getDataSet();

    auto sutDataSetIt = sutDataSet.begin();
    auto expectedDataSetIt = expectedClientDataSet.begin();

    for (std::size_t total = 0; total < expectedClientDataSet.size(); total++)
    {
        ASSERT_EQ(sutDataSetIt->data, expectedDataSetIt->data);
        ASSERT_EQ(sutDataSetIt->transactionId, expectedDataSetIt->transactionId);
        sutDataSetIt++;
        expectedDataSetIt++;
    }
}

TEST_F(ClientTest, testSetAndGetTotalTransactions)
{
    int totalTransactions = 4;

    sut->setTotalTransactions(totalTransactions);

    ASSERT_EQ(sut->getTotalTransactions(), totalTransactions);
}

}