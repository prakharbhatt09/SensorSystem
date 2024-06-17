#include <cstdint>
#include <vector>

class ITestSensor{
    public:
    //virtual std::vector <uint8_t> encode() = 0;
    virtual void addDataToBuffer(std::vector<uint8_t> &data) = 0;
    virtual std::vector<std::vector<uint8_t>> sendBufferData() = 0;
    virtual ~ITestSensor(){}
};

class TestSensor : public ITestSensor{
    public:
    std::vector<std::vector<uint8_t>> internalBuffer;

    TestSensor() = default;

    void addDataToBuffer(std::vector<uint8_t> &data) override{
            internalBuffer.push_back(data);
    };

    std::vector<std::vector<uint8_t>> sendBufferData() override{
        return internalBuffer;
    };
};

class TestSensorV4 : public ITestSensor{
    private:
    const uint16_t MessageType{0x0006};
    uint8_t NrOfSensorReadings; //assuming 4 bit
    uint8_t Rfa{0};
    std::vector <uint8_t> SensorReadingsVector;
    std::vector<std::vector<uint8_t>> internalBuffer;

    public:
    TestSensorV4() = default;

    std::vector <uint8_t> encode();

    void addDataToBuffer(std::vector<uint8_t> &data) override{
            internalBuffer.push_back(data);
    };

    std::vector<std::vector<uint8_t>> sendBufferData() override{
        return internalBuffer;
    };

    uint8_t getNrOfSensorReadings(){return NrOfSensorReadings;}
    uint8_t getRfa(){return Rfa;}

    std::vector <uint8_t> getSensorReadingsVector(){return SensorReadingsVector;}

    void setNrOfSensorReadings(uint8_t number){NrOfSensorReadings = number;}
    void setSensorReadingInVector(uint8_t reading){SensorReadingsVector.push_back(reading);}

};