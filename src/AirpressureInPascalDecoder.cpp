#include <cstdint>
#include <vector>
#include "AirpressureInPascalDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> AirpressureInPascalDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> pressureValuePascal;
    uint16_t pressure = (EncodedMessage.at(2)<<8 | EncodedMessage.at(3));
    SensorValue* value = new SensorValue(pressure,"Airpressure","Pascal");
    pressureValuePascal.push_back(value);
    return pressureValuePascal;
};