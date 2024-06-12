cmake_minimum_required(VERSION 3.5.0)
project(SensorAPI)

find_package(Catch2 REQUIRED)

include_directories(inc)

add_executable(Usage_e src/main.cpp src/SensorServer.cpp src/TemperatureInCelsiusDecoder.cpp src/TemperatureInKelvinDecoder.cpp src/MultiReadingTemperatureDecoder.cpp src/AirpressureInPascalDecoder.cpp src/CombinedSensorDecoder.cpp)

add_executable(Tests_e tests/SensorTests.cpp src/SensorServer.cpp src/TemperatureInCelsiusDecoder.cpp src/TemperatureInKelvinDecoder.cpp src/MultiReadingTemperatureDecoder.cpp src/AirpressureInPascalDecoder.cpp src/MultiReadingTemperatureDecoder.cpp src/CombinedSensorDecoder.cpp) 

add_executable(CmdEncTests_e tests/SensorTestsCmdEncode.cpp src/CommandEncoder.cpp)

target_link_libraries(Tests_e PRIVATE Catch2::Catch2WithMain)