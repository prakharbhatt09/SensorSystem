#ifndef SENSOR_HPP
#define SENSOR_HPP
#include <vector>
#include <cstdint>

using namespace std;

class I_Sensor{
    public:
    virtual vector<uint8_t> encode() = 0;
    virtual void decode(const vector <uint8_t> &EncodedMessage) = 0;
    virtual uint16_t getMessageType() = 0;
    virtual vector<uint8_t> getSensorReading() = 0;
    virtual void setSensorReading(uint8_t sensor_val) = 0;
    virtual ~I_Sensor(){};
};

class TempSensor : public I_Sensor{
    private:
    const uint16_t MessageType{0x0001};
    vector <uint8_t> SensorReadings;
    

    public:
    TempSensor() = default;

    vector<uint8_t> encode() override;
    void decode(const vector <uint8_t> &EncodedMessage) override;
    
    uint16_t getMessageType(){return MessageType;}
    vector <uint8_t> getSensorReading(){return SensorReadings;}

    void setSensorReading(uint8_t sensor_val){SensorReadings.push_back(sensor_val);}
};

class LuftdruckSensor : public I_Sensor{
    private:
    const uint16_t MessageType{0x0002};
    vector <uint8_t> SensorReadings;

    public:
    LuftdruckSensor() = default;
    
    vector<uint8_t> encode() override;
    void decode(const vector <uint8_t> &EncodedMessage) override;

    uint16_t getMessageType(){return MessageType;}
    vector <uint8_t> getSensorReading(){return SensorReadings;}

    void setSensorReading(uint8_t sensor_val){SensorReadings.push_back(sensor_val);}
}; 

class DrittSensor : public I_Sensor{
    //00 03 12 23 23 24 25 25 23 21 20 19 18 17 16 byte sequence
    private:
    const uint16_t MessageType{0x0003};
    uint8_t NrOfSensorValues;
    vector <uint8_t> SensorReadings;

    public:
    DrittSensor() = default;
    
    vector<uint8_t> encode() override;
    void decode(const vector <uint8_t> &EncodedMessage) override;

    uint16_t getMessageType(){return MessageType;}
    uint8_t getNrOfSensorValues(){return NrOfSensorValues;}
    vector <uint8_t> getSensorReading(){return SensorReadings;}

    void setNrOfSensorValues(uint8_t TotalNrOfSensorValues){NrOfSensorValues = TotalNrOfSensorValues;}
    void setSensorReading(uint8_t sensor_val){SensorReadings.push_back(sensor_val);}
};

#endif