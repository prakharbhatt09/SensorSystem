#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "fakeit.hpp"
#include "sensor.hpp"
#include "SensorFactory.hpp"
#include "SensorSystem.hpp"

using namespace std;
using namespace fakeit;

TEST_CASE("decoding a sensor msg"){

Mock<I_Sensor> mockSensor;
Mock<I_SensorFactory> mockFactory;

I_Sensor &sensor = mockSensor.get();

When(Method(mockFactory,CreateSensor)).AlwaysReturn(&sensor);
When(Method(mockSensor,decode)).AlwaysReturn();

I_SensorFactory &factory = mockFactory.get();
SensorSystem system(&factory);

vector<uint8_t> toDecode{0,1}; //because it should always have a msgTyp?
system.Decoder(toDecode);

Verify(Method(mockSensor,decode)).Exactly(1);
VerifyNoOtherInvocations(mockSensor);

}

TEST_CASE("encoding a sensor msg"){

Mock<I_Sensor> mockSensor;
Mock<I_SensorFactory> mockFactory;

I_Sensor &sensor = mockSensor.get();
When(Method(mockFactory,CreateSensor)).AlwaysReturn(&sensor);

vector<uint8_t> SensorReadings{};
When(Method(mockSensor,getSensorReading)).AlwaysReturn(SensorReadings);

vector<uint8_t> EncodedMessage{};
When(Method(mockSensor,encode)).AlwaysReturn(EncodedMessage);

I_SensorFactory &factory = mockFactory.get();
SensorSystem system(&factory);
uint8_t MessageType = 0x0002;

system.Encoder(MessageType,SensorReadings);

Verify(Method(mockSensor,encode)).Exactly(1);
VerifyNoOtherInvocations(mockSensor);

}