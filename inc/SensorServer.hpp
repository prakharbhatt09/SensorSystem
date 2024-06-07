#ifndef SENSORSERVER_HPP
#define SENSORSERVER_HPP
#include <cstdint>
#include <vector>
#include <map>
#include "TemperatureInCelsiusDecoder.hpp"
#include "TemperatureInKelvinDecoder.hpp"
#include "MultiReadingTemperatureDecoder.hpp"
#include "AirpressureInPascalDecoder.hpp"
#include "SensorValue.hpp"
#include "SensorServerInterface.hpp"

class SensorServer : public ISensorServer{
    private:
    std::map <uint16_t, IDecoder*> decoderMap;
    std::vector<SensorValue*> decodedValues; 

    public:
    SensorServer() = default;

    void initializeDecoders() override;
    void Decoder(const std::vector<uint8_t> &EncodedMessage) override;
    std::vector <SensorValue*> getDecodedValues() override;
    void addDecodedValues(SensorValue* value) override;

};
#endif