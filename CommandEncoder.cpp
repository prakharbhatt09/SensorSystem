#include <cstdint>
#include <vector>
#include "CommandEncoder.hpp"

using namespace std;

vector<uint8_t> CommandEncoder::encodeCmd(DeviceCommand command) {
        vector<uint8_t> encodedData;
        switch(command){
            case DeviceCommand::Start:
                encodedData.push_back(0x01);
                break;
            case DeviceCommand::Stop:
                encodedData.push_back(0x02);
                break;
            case DeviceCommand::Reset:
                encodedData.push_back(0x03);
                break;
        }
        return encodedData;
}