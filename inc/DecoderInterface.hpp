#ifndef DECODERINTERFACE_HPP
#define DECODERINTERFACE_HPP
#include <cstdint>
#include <vector>
#include "SensorValue.hpp"

class IDecoder{
    public:
        virtual std::vector <SensorValue*> decode(const std::vector<uint8_t> &EncodedMessage) = 0;
        virtual ~IDecoder(){}
};

#endif