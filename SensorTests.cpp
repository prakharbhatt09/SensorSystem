#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "sensor.hpp"
#include "SensorFactory.hpp"
#include "SensorSystem.hpp"

using namespace std;

TEST_CASE("encoding for Temperature Sensor")
{
   SensorFactory factory;
   SensorSystem system(&factory);
   uint16_t MessageType = 0x0001;
   vector<uint8_t> SensorReadings{0x17};

   vector<uint8_t> EncodedMessage = system.Encoder(MessageType,SensorReadings);

   CHECK(EncodedMessage.size() == 3);
   CHECK(EncodedMessage.at(0) == 0);
   CHECK(EncodedMessage.at(1) == 1);
   CHECK((uint16_t)EncodedMessage.at(2) == 23);
};

TEST_CASE("encoding for Luftdruck Sensor")
{
   SensorFactory factory;
   SensorSystem system(&factory);
   uint16_t MessageType = 0x0002;
   vector<uint8_t> SensorReadings{0x57,0x41};

   vector<uint8_t> EncodedMessage = system.Encoder(MessageType,SensorReadings);

   REQUIRE(EncodedMessage.size() == 4);
   CHECK(EncodedMessage.at(0) == 0);
   CHECK(EncodedMessage.at(1) == 2);
   CHECK((uint16_t)EncodedMessage.at(2) == 87);
   CHECK((uint16_t)EncodedMessage.at(3) == 65);
};

TEST_CASE("decoding for Temperature Sensor")
{
   SensorFactory factory;
   SensorSystem system(&factory);
   vector<uint8_t> SensorMessage{0x00,0x01,0x17};

   system.Decoder(SensorMessage);
   CHECK(system.getMessageType(SensorMessage) == 1);


   I_Sensor* TestSensor = system.getDecodedSensorInstances().back();
   REQUIRE(TestSensor != nullptr);

   vector<uint8_t> SensorReadings = TestSensor->getSensorReading();
   CHECK(SensorReadings.at(0) == 0x17);
};

TEST_CASE("decoding for Luftdruck Sensor")
{
   SensorFactory factory;
   SensorSystem system(&factory);
   vector<uint8_t> SensorMessage{0x00,0x02,0x57,0x41}; 

   system.Decoder(SensorMessage);
   CHECK(system.getMessageType(SensorMessage) == 2);

   I_Sensor* TestSensor = system.getDecodedSensorInstances().back();
   REQUIRE(TestSensor != nullptr);

   vector<uint8_t> SensorReadings = TestSensor->getSensorReading();
   CHECK(SensorReadings.at(0) == 0x57);
   CHECK(SensorReadings.at(1) == 0x41);

};

TEST_CASE("encoding for dritt sensor")
{
   SensorFactory factory;
   SensorSystem system(&factory);
   uint16_t MessageType = 0x0003;
   uint8_t NrOfSensorValues = 12;
   vector<uint8_t> SensorReadings{23,23,24,25,25,23,21,20,19,18,17,16};

   vector<uint8_t> EncodedMessage = system.Encoder(MessageType,SensorReadings);
   REQUIRE(EncodedMessage.size() == 15);
   CHECK(EncodedMessage.at(0) == 0);
   CHECK(EncodedMessage.at(1) == 3);
   CHECK(EncodedMessage.at(2) == 12);
   CHECK(EncodedMessage.at(3) == 23);
   CHECK(EncodedMessage.at(4) == 23);
   CHECK(EncodedMessage.at(5) == 24);
   CHECK(EncodedMessage.at(6) == 25);
   CHECK(EncodedMessage.at(7) == 25);
   CHECK(EncodedMessage.at(8) == 23);
   CHECK(EncodedMessage.at(9) == 21);
   CHECK(EncodedMessage.at(10) == 20);
   CHECK(EncodedMessage.at(11) == 19);
   CHECK(EncodedMessage.at(12) == 18);
   CHECK(EncodedMessage.at(13) == 17);
   CHECK(EncodedMessage.at(14) == 16);
};


TEST_CASE("decoding for Dritt Sensor")//failing test again
{
   SensorFactory factory;
   SensorSystem system(&factory);
   vector<uint8_t> SensorMessage{00,03,12,23,23,24,25,25,23,21,20,19,18,17,16}; 

   system.Decoder(SensorMessage);
   CHECK(system.getMessageType(SensorMessage) == 0x0003);

   I_Sensor* Testsensor = system.getDecodedSensorInstances().back();
   REQUIRE(Testsensor != nullptr);
   vector<uint8_t> SensorReadings = Testsensor->getSensorReading();
   CHECK(SensorReadings.size() == 12);
   CHECK(SensorReadings.at(0) == 23);
   CHECK(SensorReadings.at(1) == 23);
   CHECK(SensorReadings.at(2) == 24);
   CHECK(SensorReadings.at(3) == 25);   
   CHECK(SensorReadings.at(4) == 25);
   CHECK(SensorReadings.at(5) == 23);
   CHECK(SensorReadings.at(6) == 21);
   CHECK(SensorReadings.at(7) == 20);
   CHECK(SensorReadings.at(8) == 19);
   CHECK(SensorReadings.at(9) == 18);
   CHECK(SensorReadings.at(10) == 17);
   CHECK(SensorReadings.at(11) == 16);
};