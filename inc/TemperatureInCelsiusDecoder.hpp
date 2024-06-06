#ifndef TemperatureInCelsiusDecoder_HPP
#define TemperatureInCelsiusDecoder_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"
#include "SensorServerInterface.hpp"

using namespace std;

class TemperatureInCelsiusDecoder : public IDecoder{
    private:
    vector <SensorValue*> internalBuffer;

    public:
    TemperatureInCelsiusDecoder() = default;
    vector <SensorValue*> decode(const vector<uint8_t> &EncodedMessage) override;
};
#endif