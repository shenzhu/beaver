#pragma once

#include <memory>

#include "librdkafka/rdkafkacpp.h"

#include "config.h"

namespace beaver {

class DataStream {
public:

    DataStream(const Config& config);
    
    DataStream(Config&& config);

    // Avoid copy
    DataStream(const DataStream& rhs) = delete;
    DataStream& operator=(const DataStream& rhs) = delete;

    // Avoid move
    DataStream(DataStream&& rhs) = delete;
    DataStream& operator=(DataStream&& rhs) = delete;

    void start();

private:
    
    // Config Kafka
    template<typename T>
    void setKafkaConfig(RdKafka::Conf* conf, const char* property, T&& value);

    // Initialize Kafka consumer
    void initKafkaConsumer();

    // Consume message from Kafka brokers
    void consumeMessage(RdKafka::Message* message);
    
    Config config_;

    std::unique_ptr<RdKafka::KafkaConsumer> kafkaConsumer_;
};

}  // namespace beaver