// nguon/app/menu.cpp

#include "app/menu.h"
#include "core/device_state.h"
#include "core/command.h"
#include "ds/stack.h"
#include "io/file_io.h"
#include "ds/linked_list.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

// ===== History + counters (DS bổ sung: LinkedList) =====
static LinkedList<std::string> g_history;
static int g_undoCount = 0;
static int g_redoCount = 0;

// ===== Helpers =====
static std::vector<std::string> splitTokens(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> tok;
    std::string w;
    while (iss >> w) tok.push_back(w);
    return tok;
}

static ParamType parseParam(const std::string& s) {
    if (s == "gain")  return ParamType::GAIN;
    if (s == "range") return ParamType::RANGE;
    if (s == "mode")  return ParamType::MODE;
    return ParamType::UNKNOWN;
}

// Implemented in nguon/core/command.cpp (bạn đang có sẵn)
void applyCommand(DeviceState& st, const Command& c);
void revertCommand(DeviceState& st, const Command& c);

void runMenu() {
    DeviceState st;
    Stack<Command> undoSt(10000), redoSt(10000);

    std::cout << "UndoRedo CLI\n";
    std::cout << "Commands:\n";
    std::cout << "  set <gain|range|mode> <value>\n";
    std::cout << "  show | undo | redo | exit\n";
    std::cout << "  run <script_path>\n";
    std::cout << "  save <out_path>\n";
    std::cout << "  load <in_path>\n";
    std::cout << "  search <keyword>\n";
    std::cout << "  report <csv_path>\n";
    std::cout << "  export <csv_path>    (alias of report)\n";

    bool shouldExit = false;

    // Dùng std::function để handleLine gọi lại chính nó (khi run script / load)
    std::function<void(const std::string&)> handleLine;

    handleLine = [&](const std::string& lineRaw) {
        auto tok = splitTokens(lineRaw);
        if (tok.empty()) return;

        // alias
        if (tok[0] == "export") tok[0] = "report";

        // exit
        if (tok[0] == "exit") {
            shouldExit = true;
            return;
        }

        // show
        if (tok[0] == "show") {
            st.print();
            return;
        }

        // set
        if (tok[0] == "set") {
            if (tok.size() < 3) {
                std::cout << "Usage: set <param> <value>\n";
                return;
            }
            ParamType p = parseParam(tok[1]);
            if (p == ParamType::UNKNOWN) {
                std::cout << "Unknown param\n";
                return;
            }

            Command c;
            c.param = p;
            c.newValue = tok[2];
            c.raw = lineRaw;

            if (p == ParamType::GAIN)       c.oldValue = std::to_string(st.gain);
            else if (p == ParamType::RANGE) c.oldValue = std::to_string(st.range);
            else if (p == ParamType::MODE)  c.oldValue = st.mode;

            applyCommand(st, c);
            undoSt.push(c);
            redoSt.clear(); // set mới thì xóa redo

            // log lịch sử
            g_history.push_back(lineRaw);

            std::cout << "OK\n";
            return;
        }

        // undo
        if (tok[0] == "undo") {
            if (undoSt.empty()) {
                std::cout << "Nothing to undo\n";
                return;
            }
            Command c = undoSt.pop();
            revertCommand(st, c);
            redoSt.push(c);

            g_undoCount++;
            g_history.push_back(lineRaw);

            std::cout << "Undone\n";
            return;
        }

        // redo
        if (tok[0] == "redo") {
            if (redoSt.empty()) {
                std::cout << "Nothing to redo\n";
                return;
            }
            Command c = redoSt.pop();
            applyCommand(st, c);
            undoSt.push(c);

            g_redoCount++;
            g_history.push_back(lineRaw);

            std::cout << "Redone\n";
            return;
        }

        // run <script_path>
        if (tok[0] == "run") {
            if (tok.size() < 2) {
                std::cout << "Usage: run <script_path>\n";
                return;
            }
            std::string path = tok[1];

            bool ok = run_script_lines(path, [&](const std::string& cmdLine) {
                handleLine(cmdLine);
                if (shouldExit) return;
            });

            if (!ok) std::cout << "Cannot open: " << path << "\n";
            else std::cout << "Done.\n";
            return;
        }

        // save <out_path>  (lưu log lệnh ra file)
        if (tok[0] == "save") {
            if (tok.size() < 2) {
                std::cout << "Usage: save <out_path>\n";
                return;
            }
            std::string path = tok[1];

            bool ok = save_session_log(path, [&](std::ostream& out) {
                g_history.for_each([&](const std::string& s) {
                    out << s << "\n";
                });
            });

            std::cout << (ok ? "Saved.\n" : "Save failed.\n");
            return;
        }

        // load <in_path>  (khôi phục phiên: reset rồi replay log)
        if (tok[0] == "load") {
            if (tok.size() < 2) {
                std::cout << "Usage: load <in_path>\n";
                return;
            }
            std::string path = tok[1];

            // reset phiên làm việc
            st = DeviceState();
            undoSt.clear();
            redoSt.clear();
            g_history.clear();
            g_undoCount = 0;
            g_redoCount = 0;
            shouldExit = false;

            bool ok = run_script_lines(path, [&](const std::string& cmdLine) {
                handleLine(cmdLine);
                if (shouldExit) return;
            });

            if (!ok) std::cout << "Cannot open: " << path << "\n";
            else std::cout << "Loaded.\n";
            return;
        }

        // search <keyword>
        if (tok[0] == "search") {
            if (tok.size() < 2) {
                std::cout << "Usage: search <keyword>\n";
                return;
            }
            std::string kw = tok[1];

            int idx = 0;
            g_history.for_each([&](const std::string& s) {
                if (s.find(kw) != std::string::npos) {
                    std::cout << "[" << idx << "] " << s << "\n";
                }
                ++idx;
            });
            return;
        }

        // report <csv_path>
        if (tok[0] == "report") {
            if (tok.size() < 2) {
                std::cout << "Usage: report <csv_path>\n";
                return;
            }
            std::string path = tok[1];

            std::ofstream fout(path);
            if (!fout) {
                std::cout << "Cannot write: " << path << "\n";
                return;
            }

            // CSV kiểu "metric,value" để giảng viên dễ check
            fout << "metric,value\n";
            fout << "gain," << st.gain << "\n";
            fout << "range," << st.range << "\n";
            fout << "mode," << st.mode << "\n";
            fout << "total_history," << (int)g_history.size() << "\n";
            fout << "undo_count," << g_undoCount << "\n";
            fout << "redo_count," << g_redoCount << "\n";
            fout.close();

            std::cout << "Report exported.\n";
            return;
        }

        std::cout << "Unknown command\n";
    };

    // ===== Main loop =====
    std::string line;
    while (!shouldExit) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        handleLine(line);
    }
}
