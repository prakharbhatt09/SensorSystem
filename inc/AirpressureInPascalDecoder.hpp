#ifndef AirpressureInPascalDecoder_HPP
#define AirpressureInPascalDecoder_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

using namespace std;

class AirpressureInPascalDecoder : public IDecoder{
    public:
        vector <SensorValue*> decode(const vector<uint8_t> &EncodedMessage) override;

};
#endif