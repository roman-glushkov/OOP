#pragma once
#include <map>

struct GearRange
{
    int min;
    int max;
};

class Car
{
public:
    bool IsTurnedOn() const;
    bool TurnOnEngine();
    bool TurnOffEngine();

    bool SetGear(int gear);
    bool SetSpeed(int speed);

    int GetGear() const;
    int GetSpeed() const;

private:
    bool m_isEngineOn = false;
    int m_gear = 0;
    int m_speed = 0;

    bool IsSpeedInGearRange(int gear, int speed) const;

    static const std::map<int, GearRange> GEAR_SPEED_RANGES;
};