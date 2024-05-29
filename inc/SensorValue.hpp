#ifndef SENSORVALUE_HPP
#define SENSORVALUE_HPP
#include <cstdint>
#include <string>

using namespace std;

class SensorValue{
    private:
    double value;
    string type;
    string unit;

    public:
    SensorValue(double val_, string type_, string unit_) : value(val_), type(type_), unit(unit_) {}

    double getValue() {return value;}
    string getType() {return type;}
    string getUnit() {return unit;}
};

#endif