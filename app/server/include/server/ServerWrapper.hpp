#pragma once

#include <memory>
namespace n_server
{
class Server;

class ServerWrapper
{
public:
    ServerWrapper();
    ~ServerWrapper() = default;

    static Server& instance();
    static void interrupt(int signal);
private:
    static std::unique_ptr<Server> server;
};

}
