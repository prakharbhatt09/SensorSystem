#ifndef MultiReadingTemperatureDecoder_HPP
#define MultiReadingTemperatureDecoder_HPP
#include <cstdint>
#include <vector>
#include "DecoderInterface.hpp"
#include "SensorValue.hpp"

using namespace std;

class MultiReadingTemperatureDecoder : public IDecoder{
    public:
        vector <SensorValue*> decode(const vector<uint8_t> &EncodedMessage) override;

};
#endif