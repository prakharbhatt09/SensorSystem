#include <cstdint>
#include <vector>
#include "TemperatureInCelsiusDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> TemperatureInCelsiusDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> tempValueCelsius;
    uint8_t tempCelsius = EncodedMessage.at(2);
    SensorValue* value = new SensorValue(tempCelsius,"Temperature","Celsius");
        tempValueCelsius.push_back(value);
        return tempValueCelsius;
};