#ifndef COMBINEDSENSORDECODER_HPP
#define COMBINEDSENSORDECODER_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

class CombinedSensorDecoder : public IDecoder{
    private:
    std::vector <SensorValue*> internalBuffer;
    const uint16_t temperatureFlag = 0x0001;
    const uint16_t pressureFlag = 0x0004;

    public:
    CombinedSensorDecoder() = default;
    std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) override;
};
#endif