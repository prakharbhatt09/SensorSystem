#ifndef TEMPERATUREINKELVINDECODER_HPP
#define TEMPERATUREINKELVINDECODER_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"

class TemperatureInKelvinDecoder : public IDecoder{
    public:
    TemperatureInKelvinDecoder() = default;
    std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) override;
};
#endif