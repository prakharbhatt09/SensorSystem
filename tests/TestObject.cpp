#include "TestObject.hpp"

using namespace std;

vector <uint8_t> TestSensorV4::encode(){
    std::vector <uint8_t> EncodedMessage;
    EncodedMessage.push_back(MessageType>>8);
    EncodedMessage.push_back(MessageType &0XFF);
    EncodedMessage.push_back((getNrOfSensorReadings()<<4)|(getRfa() &0XFF));
    for(uint8_t index=0; index<getNrOfSensorReadings(); index++){
        EncodedMessage.push_back((getSensorReadingsVector().at(index)<<4)|(getRfa() &0XFF));
    }
    return EncodedMessage;
    
};