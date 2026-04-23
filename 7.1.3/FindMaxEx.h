#pragma once

#include <vector>
#include <algorithm>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
    if (arr.empty())
    {
        return false;
    }

    T tempMax = *std::max_element(arr.begin(), arr.end(), less);

    maxValue = tempMax;
    return true;
}