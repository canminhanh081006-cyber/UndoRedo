#pragma once
#include <string>
#include <functional>
#include <ostream>

bool run_script_lines(const std::string& path,
                      const std::function<void(const std::string&)>& on_line);

bool save_session_log(const std::string& path,
                      const std::function<void(std::ostream&)>& write_history);
