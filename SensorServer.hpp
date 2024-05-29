#ifndef SENSORSERVER_HPP
#define SENSORSERVER_HPP
#include <cstdint>
#include <vector>
#include <map>
#include "TemperatureInCelsiusDecoder.hpp"
#include "TemperatureInKelvinDecoder.hpp"
#include "MultiReadingTemperatureDecoder.hpp"
#include "AirpressureInPascalDecoder.hpp"
#include "DeviceCommand.hpp"

class SensorServer{
    private:
    map<uint16_t, IDecoder*> decoderMap;
    vector<SensorValue*> decodedValues;

    public:
    SensorServer(){}
    ~SensorServer(){} //delete decoder instances

    void initializeDecoders();

    void Decoder(const vector<uint8_t> &EncodedMessage);
    vector <SensorValue*> getDecodedValues() {return decodedValues;}
    
    
};

#endif