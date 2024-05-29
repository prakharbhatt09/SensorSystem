#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "CommandEncoder.hpp"
#include "DeviceCommand.hpp"

using namespace std;

TEST_CASE("Encode start command")
{
    // arrange
    CommandEncoder startCommand{};

    // Act
    vector<uint8_t> encodedData = startCommand.encodeCmd(DeviceCommand::Start);

    // Assert
    REQUIRE(encodedData.size() == 1);
    CHECK(encodedData.at(0) == 1);
};

TEST_CASE("Encode reset command"){
    CommandEncoder stopCommand;

    vector<uint8_t> encodedData = stopCommand.encodeCmd(DeviceCommand::Stop);

    REQUIRE(encodedData.size() == 1);
    CHECK(encodedData.at(0) == 2);
};

TEST_CASE("Encode stop command"){
    CommandEncoder resetCommand;

    vector<uint8_t> encodedData = resetCommand.encodeCmd(DeviceCommand::Reset);

    REQUIRE(encodedData.size() == 1);
    CHECK(encodedData.at(0) == 3);
};