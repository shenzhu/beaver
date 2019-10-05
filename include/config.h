#pragma once

#include <string>
#include <vector>

namespace beaver {

class Config {
public:

    Config(const std::string& brokers,
        const std::string& groupId,
        const std::vector<std::string>& topics);
    
    Config(std::string&& brokers,
        std::string&& groupId,
        std::vector<std::string>&& topics);

    // Copy constructors
    Config(const Config& rhs) = default;
    Config& operator=(const Config& rhs) = default;

    // Move constructors
    Config(Config&& rhs) = default;
    Config& operator=(Config&& rhs) = default;

    ~Config() {}

private:

    std::string brokers_;
    std::string groupId_;
    std::vector<std::string> topics_;
};

}  // namespace beaver