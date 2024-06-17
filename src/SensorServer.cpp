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
    decoderMap[0x0006] = new TestTemperatureDecoder();
};

void SensorServer::receiveDataFromSensor(vector <uint8_t> &SensorMessage){
    buffer.insert(buffer.end(), SensorMessage.begin(), SensorMessage.end());
};

size_t SensorServer::getMessageLength(vector <uint8_t> &MessageInBuffer){
    uint16_t MessageType = (MessageInBuffer.at(0)<<8 | MessageInBuffer.at(1));
    switch(MessageType){
        case 0x0001:
            return TEMPSENSORCELSIUSLENGTH;

        case 0x0002:
            return TEMPSENSORKELVINLENGTH;

        case 0x0003:{
            uint8_t messageLength = 2*(MessageInBuffer.at(2)) + 3;
            return messageLength;
        }
        
        case 0x0004:
            return AIRPRESSURELENGTH;

        default:
            return 0;
    }
};

void SensorServer::decodeBuffer(){
    while(buffer.size() > 2){
        auto messageLength = getMessageLength(buffer);
        if(buffer.size() >= messageLength){
            vector <uint8_t> messageFetchedFromBuffer(buffer.begin(), buffer.begin()+messageLength);
            Decoder(messageFetchedFromBuffer);
            buffer.erase(buffer.begin(), buffer.begin()+messageLength);
        }
        else{
            cout<<"not enough messages to fetch in buffer"<<endl;
            break;
        }
    }
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

vector <uint8_t> SensorServer::getServerBuffer(){
    return buffer;
};