#ifndef TEMPERATUREINCELSIUSDECODER_HPP
#define TEMPERATUREINCELSIUSDECODER_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

class TemperatureInCelsiusDecoder : public IDecoder{
    private:
    std::vector <SensorValue*> internalBuffer;

    public:
    TemperatureInCelsiusDecoder() = default;
    std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) override;
};
#endif