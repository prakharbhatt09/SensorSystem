#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "SensorServer.hpp"

using namespace std;

TEST_CASE("Server decodes for a TempSensor") {
   SensorServer server;
   server.initializeDecoders();
   
   vector<uint8_t> EncodedMessage = {0,1,23};

   server.Decoder(EncodedMessage);
   vector <SensorValue*> decodedValues = server.getDecodedValues();

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
   CHECK(decodedValues.at(0)->getValue() == 101);
   CHECK(decodedValues.at(0)->getType() == "Airpressure");
   CHECK(decodedValues.at(0)->getUnit() == "Pascal");
}