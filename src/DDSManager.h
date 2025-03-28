#ifndef _DDS_MANAGER_H_
#define _DDS_MANAGER_H_

#include <QObject>
#include <QString>
#include <QStringList>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/topic/Topic.hpp>

#include "HelloWorldMsgPubSubTypes.h"

using namespace eprosima::fastdds::dds;

class DDSManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messages READ messages NOTIFY messagesChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)

public:
    explicit DDSManager(QObject *parent = nullptr);
    virtual ~DDSManager();

    bool init();
    QStringList messages() const { return m_messages; }
    QString status() const { return m_status; }

public slots:
    void sendMessage(const QString& message);
    void startReceiving();

signals:
    void messagesChanged();
    void statusChanged();
    void messageReceived(const QString& message);

private:
    void setStatus(const QString& status);
    void addMessage(const QString& message);

    DomainParticipant* m_participant;
    Publisher* m_publisher;
    Subscriber* m_subscriber;
    Topic* m_topic;
    DataWriter* m_writer;
    DataReader* m_reader;
    TypeSupport m_type;
    QStringList m_messages;
    QString m_status;
    bool m_running;
};

#endif // _DDS_MANAGER_H_