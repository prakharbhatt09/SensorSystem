#include <cstdint>
#include <vector>
#include "MultiReadingTemperatureDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> MultiReadingTemperatureDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> tempValuesCelsius;
    uint8_t NrOfSensorReadings = EncodedMessage.at(2);
    for(uint8_t i=0; i<NrOfSensorReadings; i++){
        int index = 3+2*i;
        double tempCelsius = ((EncodedMessage.at(index)<<8) | (EncodedMessage.at(index+1)));
        SensorValue* value = new SensorValue(tempCelsius,"Temperature","Celsius");
            tempValuesCelsius.push_back(value);
    }
    return tempValuesCelsius;
};