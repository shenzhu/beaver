#include <iostream>

#include <string>
#include <vector>

#include "librdkafka/rdkafkacpp.h"

void msg_consume(RdKafka::Message* message) {
    switch (message->err()) {
        case RdKafka::ERR__TIMED_OUT:
            break;
        
        case RdKafka::ERR_NO_ERROR:
            std::cout << static_cast<int>(message->len()) << " "
                      << static_cast<const char*>(message->payload())
                      << std::endl;
            break;
        
        default:
            break;
    }
}

int main() {

    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    RdKafka::Conf* topicConf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    std::string brokers = "localhost:9092";
    std::vector<std::string> topics;
    topics.emplace_back("test");

    std::string errstr;

    conf->set("default_topic_conf", topicConf, errstr);
    conf->set("metadata.broker.list", brokers, errstr);
    conf->set("group.id", "test_group", errstr);

    RdKafka::KafkaConsumer* consumer = RdKafka::KafkaConsumer::create(conf, errstr);
    if (!consumer) {
        std::cerr << "Failed to create consumer: " << errstr << std::endl;
        exit(1);
    }

    std::cout << "% created consumer " << consumer->name() << std::endl;

    RdKafka::ErrorCode err = consumer->subscribe(topics);
    if (err) {
        std::cerr << "Failed to subscribe to " << topics.size()
                  << " topics: " << RdKafka::err2str(err)
                  << std::endl;
    }

    while (true) {
        RdKafka::Message* msg = consumer->consume(1000);
        msg_consume(msg);
        delete msg;
    }

    return 0;
}