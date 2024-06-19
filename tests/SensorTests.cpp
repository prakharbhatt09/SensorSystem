#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "SensorServer.hpp"
#include "TestObject.hpp"
#include "fakeit.hpp"

using namespace std;
using namespace fakeit;

TEST_CASE("Server decodes for a TempSensor") {
   SensorServer server;
   server.initializeDecoders();
   
   vector<uint8_t> EncodedMessage = {0,1,23};

   server.Decoder(EncodedMessage);
   vector <SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.at(0) != nullptr);
   REQUIRE(decodedValues.size() == 1);
   CHECK(decodedValues.at(0)->getValue() == 23.00);
   CHECK(decodedValues.at(0)->getType() == "Temperature");
   CHECK(decodedValues.at(0)->getUnit() == "Celsius");
}

TEST_CASE("Server decodes for a MultiReadingTemperatureSensor") {
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> EncodedMessage = {0,3,3,0,23,0,24,0,25};

   server.Decoder(EncodedMessage);
   vector <SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.size() == 3);

   CHECK(decodedValues.at(0)->getValue() == 23.00);
   CHECK(decodedValues.at(0)->getType() == "Temperature");
   CHECK(decodedValues.at(0)->getUnit() == "Celsius");

   CHECK(decodedValues.at(1)->getValue() == 24.00);
   CHECK(decodedValues.at(1)->getType() == "Temperature");
   CHECK(decodedValues.at(1)->getUnit() == "Celsius");

   CHECK(decodedValues.at(2)->getValue() == 25.00);
   CHECK(decodedValues.at(2)->getType() == "Temperature");
   CHECK(decodedValues.at(2)->getUnit() == "Celsius");
}

TEST_CASE("Server decodes for a TempSensor in Kelvin") {
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> EncodedMessage = {0,2,1,44}; //1..00101100 - 300 in binary

   server.Decoder(EncodedMessage);
   vector <SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.size() == 1);

   CHECK(decodedValues.at(0)->getValue() == 27.00);
   CHECK(decodedValues.at(0)->getType() == "Temperature");
   CHECK(decodedValues.at(0)->getUnit() == "Celsius");
}

TEST_CASE("Server decodes for a Airpressure in Pascal"){
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> EncodedMessage{0x00,0x04,0x00,0x65}; //101Pa

   server.Decoder(EncodedMessage);
   vector<SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.size() == 1);
   REQUIRE(decodedValues.at(0) != nullptr);
   CHECK(decodedValues.at(0)->getValue() == 101);
   CHECK(decodedValues.at(0)->getType() == "Airpressure");
   CHECK(decodedValues.at(0)->getUnit() == "Pascal");
}

TEST_CASE("decode scenario for 2 MultiReadingTemperatureDecoder messages") {
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> EncodedMessage1 = {0,3,3,0,23,0,24,0,25};
   vector<uint8_t> EncodedMessage2 = {0,3,3,0,26,0,27,0,28};

   server.Decoder(EncodedMessage1);
   server.Decoder(EncodedMessage2);

   vector<SensorValue*> decodedValues = server.getDecodedValues();
   REQUIRE(decodedValues.size() == 6);
   CHECK(decodedValues.at(0) != nullptr);
   CHECK(decodedValues.at(0)->getValue() == 23.00);
   CHECK(decodedValues.at(1)->getValue() == 24.00);
   CHECK(decodedValues.at(2)->getValue() == 25.00);
   CHECK(decodedValues.at(3)->getValue() == 26.00);
   CHECK(decodedValues.at(4)->getValue() == 27.00);
   CHECK(decodedValues.at(5)->getValue() == 28.00);
}

TEST_CASE("Sensor disconnect scenario for MultiReadingTemperatureDecoder with test double") {
   SensorServer server;
   TestSensor sensor;

   vector<uint8_t> EncodedMessage1 = {0,3,3,0,23,0,24,0,25};
   vector<uint8_t> EncodedMessage2 = {0,3,3,0,26,0,27,0,28};

   sensor.addDataToBuffer(EncodedMessage1);
   sensor.addDataToBuffer(EncodedMessage2);

   vector<vector<uint8_t>> bufferedData = sensor.sendBufferData();

   server.initializeDecoders();

   for(auto data : bufferedData){
      server.Decoder(data);
   } 

   vector<SensorValue*> decodedValues = server.getDecodedValues();
   REQUIRE(decodedValues.size() == 6);
   CHECK(decodedValues.at(0) != nullptr);
   CHECK(decodedValues.at(0)->getValue() == 23.00);
   CHECK(decodedValues.at(1)->getValue() == 24.00);
   CHECK(decodedValues.at(2)->getValue() == 25.00);
   CHECK(decodedValues.at(3)->getValue() == 26.00);
   CHECK(decodedValues.at(4)->getValue() == 27.00);
   CHECK(decodedValues.at(5)->getValue() == 28.00);
}

TEST_CASE("Server decodes for a CombinedSensor") {
   SensorServer server;
   server.initializeDecoders();
   
   vector<uint8_t> EncodedMessage = {0,5,0,1,23,0,4,0,101};

   server.Decoder(EncodedMessage);
   vector <SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.size() == 2);
   REQUIRE(decodedValues.at(0) != nullptr);
   REQUIRE(decodedValues.at(1) != nullptr);

   CHECK(decodedValues.at(0)->getValue() == 23.00);
   CHECK(decodedValues.at(0)->getType() == "Temperature");
   CHECK(decodedValues.at(0)->getUnit() == "Celsius");
   CHECK(decodedValues.at(1)->getValue() == 101);
   CHECK(decodedValues.at(1)->getType() == "Airpressure");
   CHECK(decodedValues.at(1)->getUnit() == "Pascal");

}

TEST_CASE("test for variation 3, 1 temp sensor readings in total"){
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> Message1 = {0,1};
   vector<uint8_t> Message2 = {23};

   server.receiveDataFromSensor(Message1);
   server.decodeBuffer();

   vector <SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.size() == 0);

   server.receiveDataFromSensor(Message2);
   server.decodeBuffer();

   vector <SensorValue*> decodedValues1 = server.getDecodedValues();

   REQUIRE(decodedValues1.size() == 1);
   CHECK(decodedValues1.at(0)->getValue() == 23.00);
}

TEST_CASE("test for variation 3, using 4 temp sensor readings in total"){
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> Message1 = {0,1};
   vector<uint8_t> Message2 = {23};
   vector<uint8_t> Message3 = {0,1,24};
   vector<uint8_t> Message4 = {0};
   vector<uint8_t> Message5 = {1,25};
   vector<uint8_t> Message6 = {0,1,26};


   server.receiveDataFromSensor(Message1);
   server.decodeBuffer();
   vector <SensorValue*> decodedValues1 = server.getDecodedValues();
   REQUIRE(decodedValues1.size() == 0);

   server.receiveDataFromSensor(Message2);
   server.decodeBuffer();
   vector <SensorValue*> decodedValues2 = server.getDecodedValues();
   decodedValues2 = server.getDecodedValues();
   REQUIRE(decodedValues2.size() == 1);

   server.receiveDataFromSensor(Message3);
   server.decodeBuffer();
   auto decodedValues3 = server.getDecodedValues();
   REQUIRE(decodedValues3.size() == 2);

   server.receiveDataFromSensor(Message4);
   server.decodeBuffer();
   auto decodedValues4 = server.getDecodedValues();
   REQUIRE(decodedValues4.size() == 2);

   server.receiveDataFromSensor(Message5);
   server.decodeBuffer();
   auto decodedValues5 = server.getDecodedValues();
   REQUIRE(decodedValues5.size() == 3);

   server.receiveDataFromSensor(Message6);
   server.decodeBuffer();
   auto decodedValues6 = server.getDecodedValues();
   REQUIRE(decodedValues6.size() == 4);

   REQUIRE(decodedValues6.size() == 4);
   REQUIRE(decodedValues6.at(0) != nullptr);
   REQUIRE(decodedValues6.at(1) != nullptr);
   REQUIRE(decodedValues6.at(2) != nullptr);
   REQUIRE(decodedValues6.at(3) != nullptr);

   CHECK(decodedValues6.at(0)->getValue() == 23.00);
   CHECK(decodedValues6.at(1)->getValue() == 24.00);
   CHECK(decodedValues6.at(2)->getValue() == 25.00);
   CHECK(decodedValues6.at(3)->getValue() == 26.00);
}

TEST_CASE("test for variation 3, to first store in server buffer and then decode"){
   SensorServer server;
   server.initializeDecoders();

   vector<uint8_t> Message1 = {0,3,6,0,23,0,24,0,25};
   vector<uint8_t> Message2 = {0,26,0,27,0,28};

   server.receiveDataFromSensor(Message1);
   server.decodeBuffer();

   vector <SensorValue*> decodedValues = server.getDecodedValues();
   REQUIRE(decodedValues.size() == 0);

   server.receiveDataFromSensor(Message2);
   server.decodeBuffer();
   
   vector <SensorValue*> decodedValues1 = server.getDecodedValues();
   
   REQUIRE(decodedValues1.size() == 6);
   CHECK(decodedValues1.at(0)->getValue() == 23.00);
   CHECK(decodedValues1.at(1)->getValue() == 24.00);
   CHECK(decodedValues1.at(2)->getValue() == 25.00);
   CHECK(decodedValues1.at(3)->getValue() == 26.00);
   CHECK(decodedValues1.at(4)->getValue() == 27.00);
   CHECK(decodedValues1.at(5)->getValue() == 28.00);

}

TEST_CASE("testing encoding and decoding variant 4 with a special test sensor for this case TestSensorV4"){
   TestSensorV4 tempSensor; //0,6,0b'0100'0000',160,160,160,160
   tempSensor.setNrOfSensorReadings(4);
   tempSensor.setSensorReadingInVector(10);
   tempSensor.setSensorReadingInVector(10);
   tempSensor.setSensorReadingInVector(10);
   tempSensor.setSensorReadingInVector(10);

   auto EncodedStream = tempSensor.encode();

   REQUIRE(EncodedStream.size() == 7);
   CHECK(EncodedStream.at(0) == 0);
   CHECK(EncodedStream.at(1) == 6);
   CHECK(uint16_t(EncodedStream.at(2)) == 64);
   CHECK(uint16_t(EncodedStream.at(3)) == 160);
   CHECK(uint16_t(EncodedStream.at(4)) == 160);
   CHECK(uint16_t(EncodedStream.at(5)) == 160);
   CHECK(uint16_t(EncodedStream.at(6)) == 160);

   SensorServer server;
   server.initializeDecoders();

   server.Decoder(EncodedStream);

   vector <SensorValue*> decodedValues = server.getDecodedValues();

   REQUIRE(decodedValues.size() == 4);
   REQUIRE(decodedValues.at(0) != nullptr);
   REQUIRE(decodedValues.at(1) != nullptr);
   REQUIRE(decodedValues.at(2) != nullptr);
   REQUIRE(decodedValues.at(3) != nullptr);

   CHECK(decodedValues.at(0)->getValue() == 10);
   CHECK(decodedValues.at(1)->getValue() == 10);
   CHECK(decodedValues.at(2)->getValue() == 10);
   CHECK(decodedValues.at(3)->getValue() == 10);  
}