#include "HelloWorld.h"

HelloWorld::HelloWorld()
    : m_index(0)
    , m_message("")
{
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::index(uint32_t _index)
{
    m_index = _index;
}

uint32_t HelloWorld::index() const
{
    return m_index;
}

void HelloWorld::message(const std::string& _message)
{
    m_message = _message;
}

std::string HelloWorld::message() const
{
    return m_message;
}