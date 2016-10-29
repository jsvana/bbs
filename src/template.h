#pragma once

#include "iac.h"

#include <experimental/optional>
#include <string>
#include <unordered_map>

class Template {
 private:
  const std::string path_;

  const std::unordered_map<std::string, std::string> commands_ = {
    {"clear_screen", shell::CLEAR_SCREEN},
    {"clear_line", shell::CLEAR_LINE},
    {"cursor_top_left", shell::CURSOR_TOP_LEFT},
  };

  const std::unordered_map<std::string, std::string> colors_ = {
    {"green", shell::GREEN},
    {"default", shell::DEFAULT},
  };

  const std::unordered_map<std::string, std::string> attributes_ = {
    {"blink", shell::BLINK},
    {"bold", shell::BOLD},
    {"default", shell::DEFAULT},
  };

  std::string body_;

  std::experimental::optional<std::string> get_code(const std::unordered_map<std::string, std::string>& map, const std::string& command);

 public:
  Template(const std::string& path) : path_(path) {}

  void calculate_body(const std::unordered_map<std::string, std::string>& vars);

  const std::string& body() { return body_; }
};
