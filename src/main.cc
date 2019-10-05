#include <iostream>

#include <string>
#include <vector>

#include "librdkafka/rdkafkacpp.h"

#include "datastream.h"

int main() {

    std::string brokers = "localhost:9092";
    std::vector<std::string> topics = {"test"};
    std::string groupId = "test_group";


    beaver::Config conf = {brokers, groupId, topics};
    beaver::DataStream dataStream = {std::move(conf)};
    dataStream.start();

    return 0;
}