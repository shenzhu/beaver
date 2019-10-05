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

    auto beforeFunc = [](std::string* key, std::string* value) {
        std::cout << "Before" << std::endl;
    };
    auto printFunc = [](std::string* key, std::string* value) {
        std::cout << *value << std::endl;
    };
    auto afterFunc = [](std::string* key, std::string* value) {
        std::cout << "After" << std::endl;
    };
    auto delimiterFunc = [](std::string* key, std::string* value) {
        std::cout << "============================" << std::endl;
    };
    dataStream.then(beforeFunc).then(printFunc).then(afterFunc).then(delimiterFunc);

    dataStream.start();

    return 0;
}