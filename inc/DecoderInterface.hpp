#ifndef DECODERINTERFACE_HPP
#define DECODERINTERFACE_HPP
#include <cstdint>
#include <vector>
#include "SensorValue.hpp"

using namespace std;

class IDecoder{
    public:
        virtual vector <SensorValue*> decode(const vector<uint8_t> &EncodedMessage) = 0;
        virtual ~IDecoder(){}
};

#endif