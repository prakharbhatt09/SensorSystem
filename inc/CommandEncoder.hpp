#ifndef COMMANDENCODER_HPP
#define COMMANDENCODER_HPP
#include <cstdint>
#include <vector>
#include "DeviceCommand.hpp"

class CommandEncoder{
    public:
    std::vector<uint8_t> encodeCmd(DeviceCommand command);
 
};

#endif