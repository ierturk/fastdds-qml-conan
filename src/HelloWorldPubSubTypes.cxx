#include "HelloWorldPubSubTypes.h"
#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

HelloWorldPubSubType::HelloWorldPubSubType()
{
    setName("HelloWorld");
    m_typeSize = static_cast<uint32_t>(sizeof(HelloWorld)) + 4 + 255; // Dynamic size for strings
    m_isGetKeyDefined = false;
    m_keyBuffer = nullptr;
}

HelloWorldPubSubType::~HelloWorldPubSubType()
{
    if (m_keyBuffer != nullptr)
    {
        free(m_keyBuffer);
    }
}

bool HelloWorldPubSubType::serialize(void* data, eprosima::fastrtps::rtps::SerializedPayload_t* payload)
{
    HelloWorld* p_type = static_cast<HelloWorld*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size);
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN);
    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    ser.serialize_encapsulation();

    try
    {
        ser << p_type->index();
        ser << p_type->message();
    }
    catch (eprosima::fastcdr::exception::NotEnoughMemoryException&)
    {
        return false;
    }

    payload->length = static_cast<uint32_t>(ser.get_serialized_data_length());
    return true;
}

bool HelloWorldPubSubType::deserialize(eprosima::fastrtps::rtps::SerializedPayload_t* payload, void* data)
{
    HelloWorld* p_type = static_cast<HelloWorld*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length);
    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN);
    deser.read_encapsulation();
    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

    try
    {
        uint32_t index;
        deser >> index;
        p_type->index(index);

        std::string message;
        deser >> message;
        p_type->message(message);
    }
    catch (eprosima::fastcdr::exception::NotEnoughMemoryException&)
    {
        return false;
    }

    return true;
}

std::function<uint32_t()> HelloWorldPubSubType::getSerializedSizeProvider(void* data)
{
    return [data]() -> uint32_t
    {
        HelloWorld* p_type = static_cast<HelloWorld*>(data);
        return static_cast<uint32_t>(sizeof(p_type->index()) + p_type->message().size() + 4);
    };
}

void* HelloWorldPubSubType::createData()
{
    return reinterpret_cast<void*>(new HelloWorld());
}

void HelloWorldPubSubType::deleteData(void* data)
{
    delete reinterpret_cast<HelloWorld*>(data);
}

bool HelloWorldPubSubType::getKey(void* data, eprosima::fastrtps::rtps::InstanceHandle_t* ihandle, bool force_md5)
{
    (void)data;
    (void)ihandle;
    (void)force_md5;
    return false;
}