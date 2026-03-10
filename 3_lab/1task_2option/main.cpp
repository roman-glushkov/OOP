#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include "Car.h"

const std::string INFO_COMMAND = "Info";
const std::string ENGINE_ON_COMMAND = "EngineOn";
const std::string ENGINE_OFF_COMMAND = "EngineOff";
const std::string SET_GEAR_COMMAND = "SetGear";
const std::string SET_SPEED_COMMAND = "SetSpeed";

const std::string UNKNOWN_COMMAND_MESSAGE = "Unknown command";
const std::string CAR_MUST_STOPPED_MESSAGE = "Car must be stopped and in neutral gear";
const std::string INVALID_ARGUMENT_MESSAGE = "Invalid command argument";
const std::string INVALID_GEAR_MESSAGE = "Invalid gear";
const std::string CANNOT_SET_GEAR_ENGINE_OFF_MESSAGE = "Cannot set gear while engine is off";
const std::string UNSUITABLE_SPEED_MESSAGE = "Unsuitable current speed";
const std::string CANNOT_REVERSE_MESSAGE = "Cannot reverse while moving";
const std::string SPEED_NEGATIVE_MESSAGE = "Speed cannot be negative";
const std::string CANNOT_SET_SPEED_ENGINE_OFF_MESSAGE = "Cannot set speed while engine is off";
const std::string CANNOT_ACCELERATE_NEUTRAL_MESSAGE = "Cannot accelerate on neutral";
const std::string SPEED_OUT_OF_GEAR_MESSAGE = "Speed is out of gear range";

std::string GetDirection(int gear, int speed)
{
    if (speed == 0)
        return "standing still";
    if (gear == -1)
        return "backward";
    return "forward";
}

bool ParseInt(const std::string& str, int& result)
{
    std::istringstream iss(str);
    iss >> result;
    return !iss.fail() && iss.eof();
}

int main()
{
    Car car;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == INFO_COMMAND)
        {
            std::cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << "\n";
            std::cout << "Direction: " << GetDirection(car.GetGear(), car.GetSpeed()) << "\n";
            std::cout << "Speed: " << car.GetSpeed() << "\n";
            std::cout << "Gear: " << car.GetGear() << "\n";
        }
        else if (command == ENGINE_ON_COMMAND)
        {
            car.TurnOnEngine();
        }
        else if (command == ENGINE_OFF_COMMAND)
        {
            if (!car.TurnOffEngine())
                std::cout << CAR_MUST_STOPPED_MESSAGE << "\n";
        }
        else if (command == SET_GEAR_COMMAND)
        {
            std::string arg;
            if (!(iss >> arg))
            {
                std::cout << INVALID_ARGUMENT_MESSAGE << "\n";
                continue;
            }
            int gear;
            if (!ParseInt(arg, gear))
            {
                std::cout << INVALID_ARGUMENT_MESSAGE << "\n";
                continue;
            }

            if (!car.SetGear(gear))
            {
                if (gear < -1 || gear > 5)
                    std::cout << INVALID_GEAR_MESSAGE << "\n";
                else if (!car.IsTurnedOn())
                    std::cout << CANNOT_SET_GEAR_ENGINE_OFF_MESSAGE << "\n";
                else if (gear == -1 && car.GetSpeed() != 0)
                    std::cout << CANNOT_REVERSE_MESSAGE << "\n";
                else
                    std::cout << UNSUITABLE_SPEED_MESSAGE << "\n";
            }
        }
        else if (command == SET_SPEED_COMMAND)
        {
            std::string arg;
            if (!(iss >> arg))
            {
                std::cout << INVALID_ARGUMENT_MESSAGE << "\n";
                continue;
            }
            int speed;
            if (!ParseInt(arg, speed))
            {
                std::cout << INVALID_ARGUMENT_MESSAGE << "\n";
                continue;
            }

            if (!car.SetSpeed(speed))
            {
                if (speed < 0)
                    std::cout << SPEED_NEGATIVE_MESSAGE << "\n";
                else if (!car.IsTurnedOn())
                    std::cout << CANNOT_SET_SPEED_ENGINE_OFF_MESSAGE << "\n";
                else if (car.GetGear() == 0 && speed > car.GetSpeed())
                    std::cout << CANNOT_ACCELERATE_NEUTRAL_MESSAGE << "\n";
                else
                    std::cout << SPEED_OUT_OF_GEAR_MESSAGE << "\n";
            }
        }
        else
        {
            std::cout << UNKNOWN_COMMAND_MESSAGE << "\n";
        }
    }

    return 0;
}