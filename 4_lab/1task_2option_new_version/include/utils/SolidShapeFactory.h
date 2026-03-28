#pragma once
#include "../interfaces/IShapeFactory.h"
#include <sstream>
#include <iostream>
#include <cctype>
#include "Config.h"

class SolidShapeFactory : public IShapeFactory
{
protected:
    bool IsValidColor(const std::string& color) const
    {
        if (color.length() != Config::COLOR_STRING_LENGTH) return false;
        for (char c : color) {
            if (!std::isxdigit(c)) return false;
        }
        return true;
    }
    
    uint32_t ColorStringToUint32(const std::string& color) const
    {
        return std::stoul(color, nullptr, 16);
    }
    
    bool ReadColors(std::istringstream& iss, std::string& outlineColorStr, std::string& fillColorStr) const
    {
        if (!(iss >> outlineColorStr >> fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_FORMAT;
            return false;
        }
        
        if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_INVALID_COLOR;
            return false;
        }
        
        return true;
    }
    
    bool ReadAndConvertColors(std::istringstream& iss, uint32_t& outlineColor, uint32_t& fillColor) const
    {
        std::string outlineColorStr, fillColorStr;
        if (!ReadColors(iss, outlineColorStr, fillColorStr)) {
            return false;
        }
        
        outlineColor = ColorStringToUint32(outlineColorStr);
        fillColor = ColorStringToUint32(fillColorStr);
        return true;
    }
    
    bool HasExtraData(std::istringstream& iss) const
    {
        std::string extra;
        if (iss >> extra) {
            std::cout << Config::ERROR_PREFIX << Config::ERROR_EXTRA_DATA;
            return true;
        }
        return false;
    }
};