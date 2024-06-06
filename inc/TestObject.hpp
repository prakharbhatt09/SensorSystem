#include <cstdint>
#include <vector>

class ITestSensor{
    public:
    virtual void addDataToBuffer(vector<uint8_t>data) = 0;
    virtual vector<vector<uint8_t>> sendBufferData() = 0;
};

class TestSensor : public ITestSensor{
    public:
    vector<vector<uint8_t>> internalBuffer;

    void addDataToBuffer(vector<uint8_t>data) override{
            internalBuffer.push_back(data);
    };

    vector<vector<uint8_t>> sendBufferData() override{
        return internalBuffer;
    };
};