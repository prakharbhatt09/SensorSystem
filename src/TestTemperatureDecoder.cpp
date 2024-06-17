#include <cstdint>
#include <vector>
#include "TestTemperatureDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> TestTemperatureDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> tempValuesCelsius;
    uint8_t NrOfSensorReadings = (EncodedMessage.at(2)>>4);
    for(uint8_t i=0; i<NrOfSensorReadings; i++){
        uint16_t tempCelsius = (EncodedMessage.at(i+3)>>4);
        SensorValue* value = new SensorValue(tempCelsius,"Temperature","Celsius");
            tempValuesCelsius.push_back(value);
    }
    return tempValuesCelsius;
};