#ifndef SENSORSERVERINTERFACE_HPP
#define SENSORSERVERINTERFACE_HPP
#include <cstdint>
#include <vector>
#include "SensorValue.hpp"

using namespace std;

class ISensorServer{
    public:
    virtual ~ISensorServer(){}
    virtual void initializeDecoders() = 0;
    virtual void Decoder(const vector<uint8_t> &EncodedMessage) = 0;
    virtual vector <SensorValue*> getDecodedValues() = 0;
    virtual void addDecodedValues(SensorValue* value) = 0;
};

#endif