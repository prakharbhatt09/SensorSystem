#include <cstdint>
#include <vector>
#include <iostream>
#include "CombinedSensorDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> CombinedSensorDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> combinedSensorValues;
    int index = 2;
    while((index+1) < EncodedMessage.size()){
        uint16_t messageFlag = (EncodedMessage.at(index)<<8 | EncodedMessage.at(index+1)); //2+3 is mtype
        index += 2;
        if(messageFlag & temperatureFlag){
            uint8_t tempCelsius = EncodedMessage.at(index); //4
            SensorValue* value = new SensorValue(tempCelsius,"Temperature","Celsius");
            combinedSensorValues.push_back(value);
            index++;
        }
        if(messageFlag & pressureFlag){
            uint16_t pressure = (EncodedMessage.at(index)<<8 | EncodedMessage.at(index+1)); //4+5
            SensorValue* value = new SensorValue(pressure,"Airpressure","Pascal");
            combinedSensorValues.push_back(value);
            index += 2;
        }
    }
    return combinedSensorValues;
};