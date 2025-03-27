#ifndef _HELLO_WORLD_PUBSUBTYPES_H_
#define _HELLO_WORLD_PUBSUBTYPES_H_

#include <fastdds/dds/topic/TopicDataType.hpp>
#include <fastrtps/rtps/common/SerializedPayload.h>
#include <fastrtps/rtps/common/InstanceHandle.h>
#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>
#include "HelloWorld.h"

class HelloWorldPubSubType : public eprosima::fastdds::dds::TopicDataType
{
public:
    HelloWorldPubSubType();
    virtual ~HelloWorldPubSubType();

    // Override pure virtual functions from TopicDataType
    bool serialize(void* data, eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;
    bool deserialize(eprosima::fastrtps::rtps::SerializedPayload_t* payload, void* data) override;
    std::function<uint32_t()> getSerializedSizeProvider(void* data) override;
    void* createData() override;
    void deleteData(void* data) override;
    bool getKey(void* data, eprosima::fastrtps::rtps::InstanceHandle_t* ihandle, bool force_md5 = false) override;

private:
    void* m_keyBuffer;
};

#endif // _HELLO_WORLD_PUBSUBTYPES_H_