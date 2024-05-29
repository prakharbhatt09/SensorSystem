#include <cstdint>
#include <vector>
#include "TemperatureInCelsiusDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> TemperatureInCelsiusDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> tempValueCelsius;
    double tempCelsius = EncodedMessage.at(2);
    tempValueCelsius.push_back(new SensorValue(tempCelsius,"Temperature","Celsius"));
    return tempValueCelsius;
};