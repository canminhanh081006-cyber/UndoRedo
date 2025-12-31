#include "core/command.h"
#include "core/device_state.h"

static void setParam(DeviceState& st, ParamType p, const std::string& v) {
    if (p == ParamType::GAIN) st.gain = std::stoi(v);
    else if (p == ParamType::RANGE) st.range = std::stoi(v);
    else if (p == ParamType::MODE) st.mode = v;
}

void applyCommand(DeviceState& st, const Command& c) {
    setParam(st, c.param, c.newValue);
}

void revertCommand(DeviceState& st, const Command& c) {
    setParam(st, c.param, c.oldValue);
}
