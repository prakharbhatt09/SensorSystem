#ifndef DEVICECOMMAND_HPP
#define DEVICECOMMAND_HPP
#include <cstdint>
#include <vector>
#include "DeviceCommand.hpp"

using namespace std;

class CommandEncoder{
    public:
    vector<uint8_t> encodeCmd(DeviceCommand command);
 
};

#endif