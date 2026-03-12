#include "Car.h"

bool Car::IsTurnedOn() const
{
    return m_isEngineOn;
}

bool Car::TurnOnEngine()
{
    if (m_isEngineOn)
    {
        return true;
    }

    m_isEngineOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (!m_isEngineOn)
    {
        return true;
    }

    if (m_speed != MIN_SPEED || m_gear != NEUTRAL_GEAR)
    {
        return false;
    }

    m_isEngineOn = false;
    return true;
}

bool Car::IsSpeedInGearRange(int gear, int speed) const
{
    const auto it = GEAR_SPEED_RANGES.find(gear);

    if (it == GEAR_SPEED_RANGES.end())
    {
        return false;
    }

    const GearRange& range = it->second;

    return speed >= range.min && speed <= range.max;
}

bool Car::SetGear(int gear)
{
    if (gear < MIN_GEAR || gear > MAX_GEAR)
    {
        return false;
    }

    if (!m_isEngineOn)
    {
        return false;
    }

    if (gear == REVERSE_GEAR && m_speed != MIN_SPEED)
    {
        return false;
    }

    if (gear > NEUTRAL_GEAR && m_direction == DIRECTION_BACKWARD && m_speed != MIN_SPEED)
    {
        return false;
    }

    if (gear != NEUTRAL_GEAR && !IsSpeedInGearRange(gear, m_speed))
    {
        return false;
    }

    m_gear = gear;

    UpdateDirection();

    return true;
}

bool Car::SetSpeed(int speed)
{
    if (speed < MIN_SPEED)
    {
        return false;
    }

    if (!m_isEngineOn)
    {
        return false;
    }

    if (m_gear == NEUTRAL_GEAR && speed > m_speed)
    {
        return false;
    }

    if (m_gear != NEUTRAL_GEAR && !IsSpeedInGearRange(m_gear, speed))
    {
        return false;
    }

    m_speed = speed;

    UpdateDirection();

    return true;
}

void Car::UpdateDirection()
{
    if (m_speed == MIN_SPEED)
    {
        m_direction = DIRECTION_STOPPED;
    }
    else if (m_gear == REVERSE_GEAR)
    {
        m_direction = DIRECTION_BACKWARD;
    }
    else if (m_gear > NEUTRAL_GEAR)
    {
        m_direction = DIRECTION_FORWARD;
    }
}

int Car::GetGear() const
{
    return m_gear;
}

int Car::GetSpeed() const
{
    return m_speed;
}

int Car::GetDirection() const
{
    return m_direction;
}