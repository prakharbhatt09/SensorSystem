#include <vector>
#include <cstdint>
#include <iostream>
#include "SensorSystem.hpp"

using namespace std;

uint16_t SensorSystem::getMessageType(const vector<uint8_t> &EncodedMessage){
    uint16_t MessageType = ((EncodedMessage.at(0)<<8)|EncodedMessage.at(1));
    return MessageType;
};

void SensorSystem::Decoder(const vector<uint8_t> &EncodedMessage){
    
    uint16_t MessageType = getMessageType(EncodedMessage);
    I_Sensor* sensor = factory->CreateSensor(MessageType);

    
    if(sensor != nullptr){
        sensor->decode(EncodedMessage);
        DecodedSensorInstances.push_back(sensor);
    }
    else
        cout<<"null pointer stored in created sensor while decoding"<<endl;

};

vector<uint8_t> SensorSystem::Encoder(uint16_t MessageType, vector<uint8_t>& SensorReadings){
    I_Sensor* sensor = factory->CreateSensor(MessageType);

    if(sensor != nullptr){

        for (uint8_t reading : SensorReadings) {
            sensor->setSensorReading(reading);
        }

        vector<uint8_t> EncodedMessage = sensor->encode();

        delete sensor;

        return EncodedMessage;
    }
    else{
        cout<<"no sensor available for this message type"<<endl;
        return {};
    }
}