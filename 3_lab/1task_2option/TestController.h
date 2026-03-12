#pragma once
#include "CarController.h"
#include <sstream>

class TestController
{
public:
    TestController() : m_controller(m_input, m_output) {}
    
    void Info()
    {
        std::istringstream args("");
        m_controller.Info(args);
    }
    
    void EngineOn()
    {
        std::istringstream args("");
        m_controller.EngineOn(args);
    }
    
    void EngineOff()
    {
        std::istringstream args("");
        m_controller.EngineOff(args);
    }
    
    void SetGear(int gear)
    {
        std::istringstream args(std::to_string(gear));
        m_controller.SetGear(args);
    }
    
    void SetSpeed(int speed)
    {
        std::istringstream args(std::to_string(speed));
        m_controller.SetSpeed(args);
    }
    
    std::string GetOutput() const
    {
        return m_output.str();
    }

private:
    std::istringstream m_input;
    std::ostringstream m_output;
    CarController m_controller;
};