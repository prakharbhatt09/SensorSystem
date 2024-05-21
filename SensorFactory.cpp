#include <vector>
#include <cstdint>
#include <iostream>
#include "SensorFactory.hpp"

using namespace std;

I_Sensor* SensorFactory::CreateSensor(uint16_t MessageType){
    I_Sensor* sensor = nullptr;
    switch(MessageType){
        case 0x0001:
            sensor = new TempSensor();
            break;

        case 0x0002:
            sensor = new LuftdruckSensor();
            break;

        case 0x0003:
            sensor = new DrittSensor();    
            break;

        default:
            cout <<"default block - no sensor found for this message type"<< endl;
            break;
    }
    return sensor;
};