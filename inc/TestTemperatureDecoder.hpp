#ifndef TESTTEMPERATUREDECODER_HPP
#define TESTTEMPERATUREDECODER_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

class TestTemperatureDecoder : public IDecoder{
    public:
    TestTemperatureDecoder() = default;
    std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) override;

};
#endif