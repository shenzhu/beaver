#pragma once

#include <functional>
#include <memory>

#include "librdkafka/rdkafkacpp.h"

#include "config.h"
#include "helper.h"

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

    template <typename F,
        typename = typename std::enable_if<
            std::is_same<ResultOf<F, std::string*, std::string*>, void>::value,
            void>::type>
    DataStream& then(F func) {
        functions_.emplace_back(func);

        return *this;
    }

    void start();

private:
    
    // Config Kafka
    template <typename T>
    void setKafkaConfig(RdKafka::Conf* conf, const char* property, T&& value);

    // Initialize Kafka consumer
    void initKafkaConsumer();

    // Consume message from Kafka brokers
    void consumeMessage(RdKafka::Message* message);

    // Apply the functions to each Kafka message
    void applyFuncs(RdKafka::Message* message);
    
    Config config_;
    std::unique_ptr<RdKafka::KafkaConsumer> kafkaConsumer_;
    std::vector<std::function<void(std::string*, std::string*)>> functions_;
};

}  // namespace beaver