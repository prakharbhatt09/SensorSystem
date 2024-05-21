#ifndef SENSORFACTORY_HPP
#define SENSORFACTORY_HPP
#include <vector>
#include <cstdint>
#include <iostream>
#include "sensor.hpp"

using namespace std;

class I_SensorFactory{
    public:
        virtual ~I_SensorFactory(){}
        virtual I_Sensor* CreateSensor(uint16_t MessageType) = 0;
};

class SensorFactory : public I_SensorFactory {
    public:
        I_Sensor* CreateSensor(uint16_t MessageType) override;

};

#endif