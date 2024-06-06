#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "fakeit.hpp"
#include "DecoderInterface.hpp"
#include "SensorServerInterface.hpp"
#include "TestObject.hpp"

using namespace std;
using namespace fakeit;

TEST_CASE("decode functionality in server"){
    Mock<ISensorServer> testServer;

    ISensorServer &server = testServer.get();

    When(Method(testServer,initializeDecoders)).Return();
    server.initializeDecoders();
    
    When(Method(testServer,Decoder)).Return();

    vector<uint8_t> EncodedMessage{};
    server.Decoder(EncodedMessage);

    Verify(Method(testServer,initializeDecoders)).Exactly(1);
    Verify(Method(testServer,Decoder)).Exactly(1);
    VerifyNoOtherInvocations(testServer);

}

TEST_CASE("checking sensor disconnect behavior, assuming 1 message in buffer"){
    Mock<ITestSensor> testSensor;
    Mock<ISensorServer> testServer;

    vector<uint8_t> EncodedMessage1 = {0,3,3,0,23,0,24,0,25};
    vector<vector<uint8_t>> bufferedData = {EncodedMessage1};
    When(Method(testSensor,sendBufferData)).AlwaysReturn(bufferedData);

    ISensorServer &server = testServer.get();

    When(Method(testServer,initializeDecoders)).Return();
    server.initializeDecoders();

    When(Method(testServer,Decoder)).AlwaysReturn();

    for(auto data : bufferedData){
       server.Decoder(data);
    }

    Verify(Method(testServer,initializeDecoders)).Exactly(1);
    Verify(Method(testServer,Decoder)).Exactly(1);
    VerifyNoOtherInvocations(testServer);
}

TEST_CASE("checking sensor disconnect behavior, assuming 2 message in buffer"){
    Mock<ITestSensor> testSensor;
    Mock<ISensorServer> testServer;

    vector<uint8_t> EncodedMessage1 = {0,3,3,0,23,0,24,0,25};
    vector<uint8_t> EncodedMessage2 = {0,3,3,0,26,0,27,0,28};

    vector<vector<uint8_t>> bufferedData = {EncodedMessage1,EncodedMessage2};
    When(Method(testSensor,sendBufferData)).AlwaysReturn(bufferedData);

    ISensorServer &server = testServer.get();

    When(Method(testServer,initializeDecoders)).Return();
    server.initializeDecoders();

    When(Method(testServer,Decoder)).AlwaysReturn();

    for(auto data : bufferedData){
       server.Decoder(data);
    }

    Verify(Method(testServer,initializeDecoders)).Exactly(1);
    Verify(Method(testServer,Decoder)).Exactly(2);
    VerifyNoOtherInvocations(testServer);
}