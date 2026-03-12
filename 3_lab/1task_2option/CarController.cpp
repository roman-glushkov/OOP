#include "CarController.h"

CarController::CarController(std::istream& input, std::ostream& output)
    : m_input(input)
    , m_output(output)
{
    m_commands[INFO_COMMAND] = [this](std::istringstream& args) { Info(args); };
    m_commands[ENGINE_ON_COMMAND] = [this](std::istringstream& args) { EngineOn(args); };
    m_commands[ENGINE_OFF_COMMAND] = [this](std::istringstream& args) { EngineOff(args); };
    m_commands[SET_GEAR_COMMAND] = [this](std::istringstream& args) { SetGear(args); };
    m_commands[SET_SPEED_COMMAND] = [this](std::istringstream& args) { SetSpeed(args); };
}

void CarController::ProcessCommands()
{
    std::string line;

    while (std::getline(m_input, line))
    {
        std::istringstream iss(line);

        std::string command;
        iss >> command;

        auto it = m_commands.find(command);

        if (it != m_commands.end())
        {
            it->second(iss);
        }
        else
        {
            m_output << UNKNOWN_COMMAND_MESSAGE << "\n";
        }
    }
}

void CarController::Info(std::istringstream&)
{
    m_output << ENGINE_OUTPUT_PREFIX << (m_car.IsTurnedOn() ? ENGINE_ON_STATE : ENGINE_OFF_STATE) << "\n";
    m_output << DIRECTION_OUTPUT_PREFIX << GetDirection(m_car.GetDirection()) << "\n";
    m_output << SPEED_OUTPUT_PREFIX << m_car.GetSpeed() << "\n";
    m_output << GEAR_OUTPUT_PREFIX << m_car.GetGear() << "\n";
}

void CarController::EngineOn(std::istringstream&)
{
    m_car.TurnOnEngine();
}

void CarController::EngineOff(std::istringstream&)
{
    if (!m_car.TurnOffEngine())
    {
        m_output << CAR_MUST_STOPPED_MESSAGE << "\n";
    }
}

void CarController::SetGear(std::istringstream& args)
{
    int gear;

    if (!(args >> gear))
    {
        m_output << INVALID_ARGUMENT_MESSAGE << "\n";
        return;
    }

    if (!m_car.SetGear(gear))
    {
        if (gear < Car::MIN_GEAR || gear > Car::MAX_GEAR)
        {
            m_output << INVALID_GEAR_MESSAGE << "\n";
        }
        else if (!m_car.IsTurnedOn())
        {
            m_output << CANNOT_SET_GEAR_ENGINE_OFF_MESSAGE << "\n";
        }
        else if (gear == Car::REVERSE_GEAR && m_car.GetSpeed() != Car::MIN_SPEED)
        {
            m_output << CANNOT_REVERSE_MESSAGE << "\n";
        }
        else
        {
            m_output << UNSUITABLE_SPEED_MESSAGE << "\n";
        }
    }
}

void CarController::SetSpeed(std::istringstream& args)
{
    int speed;

    if (!(args >> speed))
    {
        m_output << INVALID_ARGUMENT_MESSAGE << "\n";
        return;
    }

    if (!m_car.SetSpeed(speed))
    {
        if (speed < Car::MIN_SPEED)
        {
            m_output << SPEED_NEGATIVE_MESSAGE << "\n";
        }
        else if (!m_car.IsTurnedOn())
        {
            m_output << CANNOT_SET_SPEED_ENGINE_OFF_MESSAGE << "\n";
        }
        else if (m_car.GetGear() == Car::NEUTRAL_GEAR && speed > m_car.GetSpeed())
        {
            m_output << CANNOT_ACCELERATE_NEUTRAL_MESSAGE << "\n";
        }
        else
        {
            m_output << SPEED_OUT_OF_GEAR_MESSAGE << "\n";
        }
    }
}

std::string CarController::GetDirection(int direction) const
{
    if (direction == Car::DIRECTION_STOPPED)
    {
        return DIRECTION_STOPPED_STR;
    }

    if (direction == Car::DIRECTION_BACKWARD)
    {
        return DIRECTION_BACKWARD_STR;
    }

    return DIRECTION_FORWARD_STR;
}