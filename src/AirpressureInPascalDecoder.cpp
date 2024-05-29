#include <cstdint>
#include <vector>
#include "AirpressureInPascalDecoder.hpp"
#include "SensorValue.hpp"

using namespace std;

vector <SensorValue*> AirpressureInPascalDecoder::decode(const vector<uint8_t> &EncodedMessage){
    vector <SensorValue*> pressureValuePascal;
    double pressure = (EncodedMessage.at(2)<<8 | EncodedMessage.at(3));
    pressureValuePascal.push_back(new SensorValue(pressure,"Airpressure","Pascal"));
    return pressureValuePascal;
};