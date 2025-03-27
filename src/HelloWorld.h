#ifndef _HELLO_WORLD_H_
#define _HELLO_WORLD_H_

#include <string>
#include <vector>

class HelloWorld
{
public:
    HelloWorld();
    ~HelloWorld();

    void index(uint32_t _index);
    uint32_t index() const;

    void message(const std::string& _message);
    std::string message() const;

private:
    uint32_t m_index;
    std::string m_message;
};

#endif // _HELLO_WORLD_H_