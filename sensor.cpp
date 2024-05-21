#include <vector>
#include <cstdint>
#include "sensor.hpp"

using namespace std;

vector<uint8_t> TempSensor::encode(){
    vector<uint8_t> EncodedMessage;
    EncodedMessage.push_back(getMessageType()>>8);
    EncodedMessage.push_back(getMessageType());
    for(uint8_t i=0; i<getSensorReading().size(); i++){
        EncodedMessage.push_back(getSensorReading().at(i));
    }
    return EncodedMessage;
};

void TempSensor::decode(const vector <uint8_t> &EncodedMessage){
    for(uint8_t i=2; i<EncodedMessage.size(); i++){
        setSensorReading(EncodedMessage.at(i));
    }
};

vector<uint8_t> LuftdruckSensor::encode(){
    vector<uint8_t> EncodedMessage;
    EncodedMessage.push_back(getMessageType()>>8);
    EncodedMessage.push_back(getMessageType());
    for(uint8_t i=0; i<getSensorReading().size(); i+=2){
        uint16_t reading = ((getSensorReading().at(i)<<8)|(getSensorReading().at(i+1)));
        EncodedMessage.push_back(reading>>8); //87 65 ist ein messwert?
        EncodedMessage.push_back(reading &0X00FF);
    }
    return EncodedMessage;
};

void LuftdruckSensor::decode(const vector <uint8_t> &EncodedMessage){
    for(uint8_t i=2; i<EncodedMessage.size(); i+=2){
        uint16_t reading = ((EncodedMessage.at(i)<<8)|(EncodedMessage.at(i+1)));
        setSensorReading(reading>>8);
        setSensorReading(reading &0X00FF);
    }
};

vector<uint8_t> DrittSensor::encode(){
    vector<uint8_t> EncodedMessage;
    EncodedMessage.push_back(getMessageType()>>8);
    EncodedMessage.push_back(getMessageType());
    EncodedMessage.push_back(getSensorReading().size()); //for 1(c)
    for(uint8_t i=0; i<getSensorReading().size(); i++){
        EncodedMessage.push_back(getSensorReading().at(i));
    }
    return EncodedMessage;
};

void DrittSensor::decode(const vector <uint8_t> &EncodedMessage){ //check loop...
    setNrOfSensorValues(EncodedMessage.at(2)); //nach 1(c)
    for(uint8_t i=3; i<EncodedMessage.size(); i++){
        setSensorReading(EncodedMessage.at(i));
    }
};