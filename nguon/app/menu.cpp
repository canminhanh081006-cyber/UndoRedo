#include "app/menu.h"
#include "core/device_state.h"
#include "core/command.h"
#include "ds/stack.h"
#include <iostream>
#include <sstream>
#include <vector>

void applyCommand(DeviceState& st, const Command& c);
void revertCommand(DeviceState& st, const Command& c);

static ParamType parseParam(const std::string& s) {
    if (s == "gain") return ParamType::GAIN;
    if (s == "range") return ParamType::RANGE;
    if (s == "mode") return ParamType::MODE;
    return ParamType::UNKNOWN;
}

static std::vector<std::string> split(const std::string& line) {
    std::stringstream ss(line);
    std::vector<std::string> v;
    std::string w;
    while (ss >> w) v.push_back(w);
    return v;
}

void runMenu() {
    DeviceState st;
    Stack<Command> undoSt(10000), redoSt(10000);

    std::cout << "UndoRedo CLI\n";
    std::cout << "Commands: set <gain|range|mode> <value>, show, undo, redo, exit\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        auto tok = split(line);
        if (tok[0] == "exit") break;

        if (tok[0] == "show") {
            st.print();
            continue;
        }

        if (tok[0] == "set") {
            if (tok.size() < 3) { std::cout << "Usage: set <param> <value>\n"; continue; }
            ParamType p = parseParam(tok[1]);
            if (p == ParamType::UNKNOWN) { std::cout << "Unknown param\n"; continue; }

            Command c;
            c.param = p;
            c.newValue = tok[2];
            c.raw = line;

            if (p == ParamType::GAIN) c.oldValue = std::to_string(st.gain);
            else if (p == ParamType::RANGE) c.oldValue = std::to_string(st.range);
            else if (p == ParamType::MODE) c.oldValue = st.mode;

            applyCommand(st, c);
            undoSt.push(c);
            redoSt.clear(); // set mới thì xoá redo
            std::cout << "OK\n";
            continue;
        }

        if (tok[0] == "undo") {
            if (undoSt.empty()) { std::cout << "Nothing to undo\n"; continue; }
            Command c = undoSt.pop();
            revertCommand(st, c);
            redoSt.push(c);
            std::cout << "Undone\n";
            continue;
        }

        if (tok[0] == "redo") {
            if (redoSt.empty()) { std::cout << "Nothing to redo\n"; continue; }
            Command c = redoSt.pop();
            applyCommand(st, c);
            undoSt.push(c);
            std::cout << "Redone\n";
            continue;
        }

        std::cout << "Unknown command\n";
    }
}
