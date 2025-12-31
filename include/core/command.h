#pragma once
#include <string>

enum class ParamType { GAIN, RANGE, MODE, UNKNOWN };

struct Command {
    ParamType param = ParamType::UNKNOWN;
    std::string oldValue;
    std::string newValue;
    std::string raw; // lưu lệnh gốc để log/search
};
