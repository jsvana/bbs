#include "template.h"

#include <fstream>
#include <iostream>

std::experimental::optional<std::string> Template::get_code(const std::unordered_map<std::string, std::string>& map, const std::string& command) {
  auto iter = map.find(command);
  if (iter == map.end()) {
    return {};
  }

  return iter->second;
}

void Template::calculate_body(const std::unordered_map<std::string, std::string>& vars) {
  std::ifstream template_f(path_);

  if (!template_f.is_open()) {
    std::cerr << "Unable to open template \"" << path_ << "\"" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(template_f, line)) {
    if (line == "") {
      continue;
    }

    // Parse commands
    if (line[0] == '!') {
      auto end = line.find(' ');
      std::string cmd;

      if (end == std::string::npos) {
        // Full line command
        cmd = line.substr(1);
        auto code = get_code(commands_, cmd);
        if (code) {
          body_ += *code + "\r\n";
        }
      } else {
        // Command with argument(s)
        cmd = line.substr(1, end - 1);
        auto start = end + 1;
        end = line.find(' ', start);
        if (end != std::string::npos) {
          std::cerr << "Bad command: \"" << line << "\" (too many arguments)" << std::endl;
          continue;
        }
        auto arg = line.substr(start);
        std::experimental::optional<std::string> code;
        if (cmd == "color") {
          code = get_code(colors_, arg);
        } else if (cmd == "attr") {
          code = get_code(attributes_, arg);
        } else if (cmd == "prompt") {
          body_ += line.substr(start) + " ";
          continue;
        }

        if (code) {
          body_ += *code;
        }
      }
    } else {
      body_ += line + "\r\n";
    }
  }
}
