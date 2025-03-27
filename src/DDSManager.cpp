#include "DDSManager.h"
#include <QTimer>
#include <QThread>
#include <QDebug>

DDSManager::DDSManager(QObject *parent) 
    : QObject(parent)
    , m_participant(nullptr)
    , m_publisher(nullptr)
    , m_subscriber(nullptr)
    , m_topic(nullptr)
    , m_writer(nullptr)
    , m_reader(nullptr)
    , m_type(new HelloWorldPubSubType())
    , m_running(false)
{
    setStatus("Initializing...");
}

DDSManager::~DDSManager()
{
    m_running = false;
    
    if (m_reader != nullptr) {
        m_subscriber->delete_datareader(m_reader);
    }
    
    if (m_writer != nullptr) {
        m_publisher->delete_datawriter(m_writer);
    }
    
    if (m_subscriber != nullptr) {
        m_participant->delete_subscriber(m_subscriber);
    }
    
    if (m_publisher != nullptr) {
        m_participant->delete_publisher(m_publisher);
    }
    
    if (m_topic != nullptr) {
        m_participant->delete_topic(m_topic);
    }
    
    DomainParticipantFactory::get_instance()->delete_participant(m_participant);
    
    setStatus("Shutdown complete");
}

bool DDSManager::init()
{
    setStatus("Creating participant...");
    
    // Create participant
    m_participant = DomainParticipantFactory::get_instance()->create_participant(0, PARTICIPANT_QOS_DEFAULT);
    if (m_participant == nullptr) {
        setStatus("Error creating participant");
        return false;
    }

    // Register type
    m_type.register_type(m_participant);

    // Create topic
    setStatus("Creating topic...");
    m_topic = m_participant->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);
    if (m_topic == nullptr) {
        setStatus("Error creating topic");
        return false;
    }

    // Create publisher
    setStatus("Creating publisher...");
    m_publisher = m_participant->create_publisher(PUBLISHER_QOS_DEFAULT);
    if (m_publisher == nullptr) {
        setStatus("Error creating publisher");
        return false;
    }

    // Create datawriter
    m_writer = m_publisher->create_datawriter(m_topic, DATAWRITER_QOS_DEFAULT);
    if (m_writer == nullptr) {
        setStatus("Error creating datawriter");
        return false;
    }

    // Create subscriber
    setStatus("Creating subscriber...");
    m_subscriber = m_participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT);
    if (m_subscriber == nullptr) {
        setStatus("Error creating subscriber");
        return false;
    }

    // Create datareader
    m_reader = m_subscriber->create_datareader(m_topic, DATAREADER_QOS_DEFAULT);
    if (m_reader == nullptr) {
        setStatus("Error creating datareader");
        return false;
    }

    setStatus("DDS initialized successfully");
    return true;
}

void DDSManager::sendMessage(const QString& message)
{
    if (m_writer == nullptr) {
        setStatus("Writer not initialized");
        return;
    }

    static int index = 0;
    HelloWorld hello;
    hello.index(++index);
    hello.message(message.toStdString());

    if (static_cast<ReturnCode_t>(m_writer->write(&hello)) == ReturnCode_t::RETCODE_OK) {
        setStatus("Message sent: " + message);
        addMessage("Sent: " + message);
    } else {
        setStatus("Error sending message");
    }
}

void DDSManager::startReceiving()
{
    if (m_reader == nullptr) {
        setStatus("Reader not initialized");
        return;
    }

    m_running = true;
    setStatus("Started receiving messages");

    // Use a timer to periodically check for messages
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        HelloWorld hello;
        SampleInfo info;

        if (m_reader->take_next_sample(&hello, &info) == ReturnCode_t::RETCODE_OK) {
            if (info.valid_data) {
                QString msg = QString::fromStdString(hello.message());
                setStatus("Received: " + msg);
                addMessage("Received: " + msg);
                emit messageReceived(msg);
            }
        }
    });
    
    timer->start(100); // Check every 100ms
}

void DDSManager::setStatus(const QString& status)
{
    m_status = status;
    qDebug() << "Status: " << status;
    emit statusChanged();
}

void DDSManager::addMessage(const QString& message)
{
    m_messages.append(message);
    if (m_messages.size() > 100) {
        m_messages.removeFirst();
    }
    emit messagesChanged();
}