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

auto Config::brokers() const noexcept -> const decltype(brokers_)& {
    return brokers_;
}

auto Config::groupId() const noexcept-> const decltype(groupId_)& {
    return groupId_;
}

auto Config::topics() const noexcept -> const decltype(topics_)& {
    return topics_;
}

}  // namespace beaver