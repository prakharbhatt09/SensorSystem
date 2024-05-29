#ifndef ENCODERINTERFACE_HPP
#define ENCODERINTERFACE_HPP
#include <cstdint>
#include <vector>
#include "DeviceCommand.hpp"
#include "SensorValue.hpp"

using namespace std;

class IEncoder{
    ~IEncoder(){}
    virtual vector<uint8_t> encodeData(SensorValue value) = 0;
};

class TempSensorInCelsiusEncoder : public IEncoder{
    private:
    const uint16_t MessageType{0x0001};
    DeviceCommand state;
    vector<SensorValue> tempValueCelsius;

    public:
    vector<uint8_t> encodeData(SensorValue value) override;

    uint16_t getMessageType(){return MessageType;}

};
#endif