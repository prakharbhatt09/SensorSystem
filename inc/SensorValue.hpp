#ifndef SENSORVALUE_HPP
#define SENSORVALUE_HPP
#include <cstdint>
#include <string>

class SensorValue{
    private:
    double value;
    std::string type;
    std::string unit;

    public:
    SensorValue(double val_, std::string type_, std::string unit_) : value(val_), type(type_), unit(unit_) {}

    double getValue() {return value;}
    std::string getType() {return type;}
    std::string getUnit() {return unit;}
};

#endif