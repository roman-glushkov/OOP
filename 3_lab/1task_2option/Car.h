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
    int GetDirection() const;

    static constexpr int MIN_GEAR = -1;
    static constexpr int MAX_GEAR = 5;
    static constexpr int NEUTRAL_GEAR = 0;
    static constexpr int REVERSE_GEAR = -1;
    static constexpr int DIRECTION_STOPPED = 0;
    static constexpr int DIRECTION_FORWARD = 1;
    static constexpr int DIRECTION_BACKWARD = -1;
    static constexpr int MIN_SPEED = 0;
    static constexpr int INITIAL_GEAR = 0;
    static constexpr int INITIAL_SPEED = 0;
    static constexpr int INITIAL_DIRECTION = 0;

    static const std::map<int, GearRange> GEAR_SPEED_RANGES;

private:
    bool m_isEngineOn = false;
    int m_gear = INITIAL_GEAR;
    int m_speed = INITIAL_SPEED;
    int m_direction = INITIAL_DIRECTION;

    bool IsSpeedInGearRange(int gear, int speed) const;
    void UpdateDirection();
};

inline const std::map<int, GearRange> Car::GEAR_SPEED_RANGES = {
    {-1, {0, 20}},
    {1, {0, 30}},
    {2, {20, 50}},   
    {3, {30, 60}},  
    {4, {40, 90}},  
    {5, {50, 150}}   
};