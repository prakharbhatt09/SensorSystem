#ifndef SENSORSERVER_HPP
#define SENSORSERVER_HPP
#include <cstdint>
#include <vector>
#include <map>
#include "TemperatureInCelsiusDecoder.hpp"
#include "TemperatureInKelvinDecoder.hpp"
#include "MultiReadingTemperatureDecoder.hpp"
#include "AirpressureInPascalDecoder.hpp"
#include "SensorValue.hpp"
#include "SensorServerInterface.hpp"
#include "CombinedSensorDecoder.hpp"
#define TEMPSENSORCELSIUSLENGTH 3
#define TEMPSENSORKELVINLENGTH 4
#define AIRPRESSURELENGTH 4

class SensorServer : public ISensorServer{
    private:
    std::map <uint16_t, IDecoder*> decoderMap;
    std::vector<SensorValue*> decodedValues;
    std::vector <uint8_t> buffer;

    public:
    SensorServer() = default;

    void initializeDecoders() override;
    void Decoder(const std::vector<uint8_t> &EncodedMessage) override;
    std::vector <SensorValue*> getDecodedValues() override;
    void addDecodedValues(SensorValue* value) override;
    void receiveDataFromSensor(std::vector <uint8_t> &SensorMessage);
    void decodeBuffer();
    std::size_t getMessageLength(std::vector <uint8_t> &MessageInBuffer);
    std::vector <uint8_t> getServerBuffer();

};
#endif