#include "Car.h"
#include <map>

const std::map<int, GearRange> Car::GEAR_SPEED_RANGES =
{
    {-1, {0, 20}},
    {1,  {0, 30}},
    {2,  {20, 50}},
    {3,  {30, 60}},
    {4,  {40, 90}},
    {5,  {50, 150}}
};

bool Car::IsTurnedOn() const
{
    return m_isEngineOn;
}

bool Car::TurnOnEngine()
{
    if (m_isEngineOn)
        return true;

    m_isEngineOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (!m_isEngineOn)
        return true;

    if (m_speed != 0 || m_gear != 0)
        return false;

    m_isEngineOn = false;
    return true;
}

bool Car::IsSpeedInGearRange(int gear, int speed) const
{
    const auto it = GEAR_SPEED_RANGES.find(gear);
    if (it == GEAR_SPEED_RANGES.end())
        return false;

    const GearRange& range = it->second;
    return speed >= range.min && speed <= range.max;
}

bool Car::SetGear(int gear)
{
    if (gear < -1 || gear > 5)
        return false;

    if (!m_isEngineOn)
        return false;

    if (gear == -1 && m_speed != 0)
        return false;

    if (gear != 0 && !IsSpeedInGearRange(gear, m_speed))
        return false;

    m_gear = gear;
    return true;
}

bool Car::SetSpeed(int speed)
{
    if (speed < 0)
        return false;

    if (!m_isEngineOn)
        return false;

    if (m_gear == 0 && speed > m_speed)
        return false;

    if (m_gear != 0 && !IsSpeedInGearRange(m_gear, speed))
        return false;

    m_speed = speed;
    return true;
}

int Car::GetGear() const
{
    return m_gear;
}

int Car::GetSpeed() const
{
    return m_speed;
}