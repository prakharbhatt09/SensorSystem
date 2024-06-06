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
#include "SensorServerInterface.hpp"

using namespace std;

class SensorServer : public ISensorServer{
    private:
    map <uint16_t, IDecoder*> decoderMap;
    vector<SensorValue*> decodedValues; 

    public:
    SensorServer() = default;

    void initializeDecoders() override;
    void Decoder(const vector<uint8_t> &EncodedMessage) override;
    vector <SensorValue*> getDecodedValues() {return decodedValues;}
    void addDecodedValues(SensorValue* value) override;

};
#endif