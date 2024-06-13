#ifndef MULTIREADINGTEMPERATUREDECODER_HPP
#define MULTIREADINGTEMPERATUREDECODER_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

class MultiReadingTemperatureDecoder : public IDecoder{
    public:
    MultiReadingTemperatureDecoder() = default;
    std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) override;

};
#endif