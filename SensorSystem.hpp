#ifndef SENSORSYSTEM_HPP
#define SENSORSYSTEM_HPP
#include <vector>
#include <cstdint>
#include <iostream>
#include "SensorFactory.hpp"

using namespace std;

class I_SensorSystem{
    public:
    virtual ~I_SensorSystem(){}
    virtual uint16_t getMessageType(const vector<uint8_t> &EncodedMessage) = 0;
    virtual void Decoder(const vector<uint8_t> &EncodedMessage) = 0;
    virtual vector<uint8_t> Encoder(uint16_t MessageType, vector<uint8_t>& SensorReadings) = 0;
};

class SensorSystem : public I_SensorSystem{
    private:
        vector<I_Sensor*> DecodedSensorInstances;
        I_SensorFactory* factory;

    public:
        SensorSystem() = default;
        SensorSystem(I_SensorFactory* factory) : factory(factory){}
        ~SensorSystem(){
            for(I_Sensor* instance : DecodedSensorInstances){
                delete instance;
            }
        }

        uint16_t getMessageType(const vector<uint8_t> &EncodedMessage) override;
        void Decoder(const vector<uint8_t> &EncodedMessage) override;
        vector<uint8_t> Encoder(uint16_t MessageType, vector<uint8_t> &SensorReadings) override;
        vector<I_Sensor*> getDecodedSensorInstances(){return DecodedSensorInstances;}
};

#endif