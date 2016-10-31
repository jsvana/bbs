#include "template.h"

#include <fstream>
#include <iostream>

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
        if (cmd == "color") {
          auto code = get_code<shell::Color>(colors_, arg);
          if (code) {
            color_ = *code;
            // TODO(jsvana): support background colors
            body_ += color(color_, shell::Color::NONE);
          }
        } else if (cmd == "attr") {
          auto code = get_code<shell::Attribute>(attributes_, arg);
          if (code) {
            attribute_ = *code;
            body_ += attr(attribute_);
          }
        } else if (cmd == "prompt") {
          body_ += line.substr(start) + " ";
          continue;
        }
      }
    } else {
      body_ += line + "\r\n";
    }
  }
}
