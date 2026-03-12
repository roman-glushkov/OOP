#pragma once
#include <map>
#include <string>
#include <functional>
#include <istream>
#include <ostream>
#include <sstream>
#include "Car.h"

class CarController
{
public:
    CarController(std::istream& input, std::ostream& output);
    void ProcessCommands();

    void Info(std::istringstream& args);
    void EngineOn(std::istringstream& args);
    void EngineOff(std::istringstream& args);
    void SetGear(std::istringstream& args);
    void SetSpeed(std::istringstream& args);

private:
    using Command = std::function<void(std::istringstream&)>;

    std::istream& m_input;
    std::ostream& m_output;

    Car m_car;

    std::map<std::string, Command> m_commands;

    std::string GetDirection(int direction) const;

private:
    static constexpr const char* INFO_COMMAND = "Info";
    static constexpr const char* ENGINE_ON_COMMAND = "EngineOn";
    static constexpr const char* ENGINE_OFF_COMMAND = "EngineOff";
    static constexpr const char* SET_GEAR_COMMAND = "SetGear";
    static constexpr const char* SET_SPEED_COMMAND = "SetSpeed";

    static constexpr const char* ENGINE_ON_STATE = "on";
    static constexpr const char* ENGINE_OFF_STATE = "off";

    static constexpr const char* DIRECTION_STOPPED_STR = "standing still";
    static constexpr const char* DIRECTION_BACKWARD_STR = "backward";
    static constexpr const char* DIRECTION_FORWARD_STR = "forward";

    static constexpr const char* UNKNOWN_COMMAND_MESSAGE = "Unknown command";
    static constexpr const char* CAR_MUST_STOPPED_MESSAGE = "Car must be stopped and in neutral gear";
    static constexpr const char* INVALID_ARGUMENT_MESSAGE = "Invalid command argument";
    static constexpr const char* INVALID_GEAR_MESSAGE = "Invalid gear";
    static constexpr const char* CANNOT_SET_GEAR_ENGINE_OFF_MESSAGE = "Cannot set gear while engine is off";
    static constexpr const char* UNSUITABLE_SPEED_MESSAGE = "Unsuitable current speed";
    static constexpr const char* CANNOT_REVERSE_MESSAGE = "Cannot reverse while moving";
    static constexpr const char* SPEED_NEGATIVE_MESSAGE = "Speed cannot be negative";
    static constexpr const char* CANNOT_SET_SPEED_ENGINE_OFF_MESSAGE = "Cannot set speed while engine is off";
    static constexpr const char* CANNOT_ACCELERATE_NEUTRAL_MESSAGE = "Cannot accelerate on neutral";
    static constexpr const char* SPEED_OUT_OF_GEAR_MESSAGE = "Speed is out of gear range";

    static constexpr const char* ENGINE_OUTPUT_PREFIX = "Engine: ";
    static constexpr const char* DIRECTION_OUTPUT_PREFIX = "Direction: ";
    static constexpr const char* SPEED_OUTPUT_PREFIX = "Speed: ";
    static constexpr const char* GEAR_OUTPUT_PREFIX = "Gear: ";
};