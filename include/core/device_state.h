#pragma once
#include <string>
#include <iostream>

struct DeviceState {
    int gain = 0;
    int range = 0;
    std::string mode = "AUTO";

    void print() const {
        std::cout << "gain=" << gain
                  << ", range=" << range
                  << ", mode=" << mode << "\n";
    }
};
