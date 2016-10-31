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

  const std::unordered_map<std::string, shell::Color> colors_ = {
    // TODO(jsvana): make this not suck
    {"black", shell::Color::BLACK},
    {"red", shell::Color::RED},
    {"green", shell::Color::GREEN},
    {"yellow", shell::Color::YELLOW},
    {"blue", shell::Color::BLUE},
    {"magenta", shell::Color::MAGENTA},
    {"cyan", shell::Color::CYAN},
    {"white", shell::Color::WHITE},
  };

  const std::unordered_map<std::string, shell::Attribute> attributes_ = {
    {"clear", shell::Attribute::NONE},
    {"bold", shell::Attribute::BOLD},
    {"blink", shell::Attribute::BLINK},
  };

  std::string body_;

  shell::Color color_;
  shell::Attribute attribute_;

  template<typename T>
  std::experimental::optional<T> get_code(const std::unordered_map<std::string, T>& map, const std::string& command) {
    auto iter = map.find(command);
    if (iter == map.end()) {
      return {};
    }

    return iter->second;
  }

 public:
  Template(const std::string& path) : path_(path) {}

  void calculate_body(const std::unordered_map<std::string, std::string>& vars);

  const std::string& body() { return body_; }
};
