#ifndef TemperatureInKelvinDecoder_HPP
#define TemperatureInKelvinDecoder_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorServerInterface.hpp"

using namespace std;

class TemperatureInKelvinDecoder : public IDecoder{
    private:
    vector <SensorValue*> internalBuffer;

    public:
    TemperatureInKelvinDecoder() = default;
    vector <SensorValue*> decode(const vector<uint8_t> &EncodedMessage) override;
};
#endif