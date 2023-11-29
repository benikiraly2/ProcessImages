#pragma once

namespace custom_exceptions
{

class CustomException
{
public:
    virtual const char* what() const = 0;
};

class SocketAcceptException : public CustomException
{
public:
    const char* what() const override;
};

class SocketAttachException : public CustomException
{
public:
    const char* what() const override;
};

class SocketCreationException : public CustomException
{
public:
    const char* what() const override;
};

class SocketOptionSetException : public CustomException
{
public:
    const char* what() const override;
};

class SocketListenException : public CustomException
{
public:
    const char* what() const override;
};

}