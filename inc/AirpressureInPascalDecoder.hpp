#ifndef AIRPRESSUREINPASCALDECODER_HPP
#define AIRPRESSUREINPASCALDECODER_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

class AirpressureInPascalDecoder : public IDecoder{
    public:
        std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) override;

};
#endif