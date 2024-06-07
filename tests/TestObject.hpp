#include <cstdint>
#include <vector>

class ITestSensor{
    public:
    virtual void addDataToBuffer(std::vector<uint8_t>data) = 0;
    virtual std::vector<std::vector<uint8_t>> sendBufferData() = 0;
};

class TestSensor : public ITestSensor{
    public:
    std::vector<std::vector<uint8_t>> internalBuffer;

    void addDataToBuffer(std::vector<uint8_t>data) override{
            internalBuffer.push_back(data);
    };

    std::vector<std::vector<uint8_t>> sendBufferData() override{
        return internalBuffer;
    };
};