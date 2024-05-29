#include <cstdint>
#include <vector>
#include "TemperatureInKelvinDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> TemperatureInKelvinDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> tempValueCelsius;
    double tempKelvin = (EncodedMessage.at(2)<<8 | EncodedMessage.at(3));
    double tempCelsius = (tempKelvin - 273);
    tempValueCelsius.push_back(new SensorValue(tempCelsius,"Temperature","Celsius"));
    return tempValueCelsius;
    
};