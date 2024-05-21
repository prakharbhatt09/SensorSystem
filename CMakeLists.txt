cmake_minimum_required(VERSION 3.5.0)
project(SensorAPI)

find_package(Catch2 REQUIRED)

add_executable(Usage_e main.cpp sensor.hpp sensor.cpp SensorFactory.cpp SensorSystem.cpp) 

add_executable(Tests_e SensorTests.cpp sensor.cpp SensorFactory.cpp SensorSystem.cpp) 

target_link_libraries(Tests_e PRIVATE Catch2::Catch2WithMain)

add_executable(Mock_e MockTestsSensor.cpp sensor.cpp SensorFactory.cpp SensorSystem.cpp)