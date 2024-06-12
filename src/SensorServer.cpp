#include <cstdint>
#include <vector>
#include <iostream>
#include "DecoderInterface.hpp"
#include "SensorServer.hpp"

using namespace std;

void SensorServer::initializeDecoders(){
    decoderMap[0x0001] = new TemperatureInCelsiusDecoder();
    decoderMap[0x0002] = new TemperatureInKelvinDecoder();
    decoderMap[0x0003] = new MultiReadingTemperatureDecoder();
    decoderMap[0x0004] = new AirpressureInPascalDecoder();
    decoderMap[0x0005] = new CombinedSensorDecoder();
};

void SensorServer::Decoder(const vector<uint8_t> &EncodedMessage){
    uint16_t MessageType = (EncodedMessage.at(0)<<8 | EncodedMessage.at(1));
    if(decoderMap.find(MessageType) != decoderMap.end()){
        vector<SensorValue*> values = decoderMap[MessageType]->decode(EncodedMessage);
        for(SensorValue* value : values){
            decodedValues.push_back(value);
        }
    }
};

vector <SensorValue*> SensorServer::getDecodedValues(){
    return decodedValues;  
};

void SensorServer::addDecodedValues(SensorValue* value){
    if(value != nullptr){
        decodedValues.push_back(value);
    }
};