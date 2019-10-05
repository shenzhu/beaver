#include "config.h"

namespace beaver {

Config::Config(const std::string& brokers,
    const std::string& groupId,
    const std::vector<std::string>& topics) : 
    brokers_(brokers), groupId_(groupId), topics_(topics) {

}

Config::Config(std::string&& brokers,
    std::string&& groupId,
    std::vector<std::string>&& topics) :
    brokers_(brokers), groupId_(groupId), topics_(topics) {

}

}  // namespace beaver