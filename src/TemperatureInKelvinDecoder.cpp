#include <cstdint>
#include <vector>
#include "TemperatureInKelvinDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> TemperatureInKelvinDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> tempValueCelsius;
    uint16_t tempKelvin = (EncodedMessage.at(2)<<8 | EncodedMessage.at(3));
    uint16_t tempCelsius = (tempKelvin - 273);
    SensorValue* value = new SensorValue(tempCelsius,"Temperature","Celsius");
    tempValueCelsius.push_back(value);
    return tempValueCelsius;    
};