#include "io/file_io.h"
#include <fstream>
#include <string>

bool run_script_lines(const std::string& path,
                      const std::function<void(const std::string&)>& on_line) {
    std::ifstream fin(path);
    if (!fin) return false;

    std::string line;
    while (std::getline(fin, line)) {
        // trim đơn giản
        while (!line.empty() && (line.back()=='\r' || line.back()=='\n')) line.pop_back();
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        on_line(line);
    }
    return true;
}

bool save_session_log(const std::string& path,
                      const std::function<void(std::ostream&)>& write_history) {
    std::ofstream fout(path);
    if (!fout) return false;
    write_history(fout);
    return true;
}
