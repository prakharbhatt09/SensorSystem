#ifndef SENSORSERVERINTERFACE_HPP
#define SENSORSERVERINTERFACE_HPP
#include <cstdint>
#include <vector>
#include "SensorValue.hpp"

class ISensorServer{
    public:
    virtual ~ISensorServer(){}
    virtual void initializeDecoders() = 0;
    virtual void Decoder(const std::vector<uint8_t> &EncodedMessage) = 0;
    virtual std::vector <SensorValue*> getDecodedValues() = 0;
    virtual void addDecodedValues(SensorValue* value) = 0;
};

#endif