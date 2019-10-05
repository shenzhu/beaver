#include <iostream>

#include "librdkafka/rdkafkacpp.h"

#include "datastream.h"

namespace beaver {

DataStream::DataStream(const Config& config) :
    config_(config), kafkaConsumer_(nullptr) {

    initKafkaConsumer();

}

DataStream::DataStream(Config&& config) :
    config_(config), kafkaConsumer_(nullptr) {

    initKafkaConsumer();

}

template<typename T>
void DataStream::setKafkaConfig(RdKafka::Conf* conf, const char* property, T&& value) {
    std::string errstr;
    conf->set(property, std::forward<T>(value), errstr);
}

void DataStream::initKafkaConsumer() {
    // Create Kafka confs
    auto conf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    auto topicConf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC));

    // Set topic conf
    setKafkaConfig(conf.get(), "default_topic_conf", topicConf.get());
    setKafkaConfig(conf.get(), "metadata.broker.list", config_.brokers());
    setKafkaConfig(conf.get(), "group.id", config_.groupId());

    // Initialize kafka
    std::string errstr;
    kafkaConsumer_ = std::unique_ptr<RdKafka::KafkaConsumer>(RdKafka::KafkaConsumer::create(conf.get(), errstr));
    if (!kafkaConsumer_) {
        std::cerr << "Failed to create consumer: " << errstr << std::endl;
        exit(1);
    }
    std::cout << "% created consumer " << kafkaConsumer_->name() << std::endl;

    // Subscribe topics
    RdKafka::ErrorCode errCode = kafkaConsumer_->subscribe(config_.topics());
    if (errCode) {
        std::cerr << "Failed to subscribe to " << config_.topics().size()
            << " topics: " << RdKafka::err2str(errCode)
            << std::endl;
    }
}

void DataStream::consumeMessage(RdKafka::Message* message) {
    switch (message->err()) {
        case RdKafka::ERR__TIMED_OUT:
            break;
        
        case RdKafka::ERR_NO_ERROR:
            std::cout << "Key: " << message->key() << " "
                << static_cast<int>(message->len()) << " "
                << static_cast<const char*>(message->payload())
                << std::endl;
            break;
        
        case RdKafka::ERR__UNKNOWN_TOPIC:
        case RdKafka::ERR__UNKNOWN_PARTITION:
            std::cerr << "Consume failed: " << message->errstr() << std::endl;
            break;
        
        default:
            std::cerr << "Consume failed: " << message->errstr() << std::endl;
    }
}

void DataStream::start() {
    while (true) {
        RdKafka::Message* message = kafkaConsumer_->consume(1000);
        consumeMessage(message);
        delete message;
    }
}

}  // namespace beaver