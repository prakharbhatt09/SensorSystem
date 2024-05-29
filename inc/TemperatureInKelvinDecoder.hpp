#ifndef TemperatureInKelvinDecoder_HPP
#define TemperatureInKelvinDecoder_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

using namespace std;

class TemperatureInKelvinDecoder : public IDecoder{
    public:
        vector <SensorValue*> decode(const vector<uint8_t> &EncodedMessage) override;

};
#endif