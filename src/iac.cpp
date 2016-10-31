#include "iac.h"

#include <iostream>

namespace iac {

const std::string do_cmd(const unsigned char cmd) {
  return {(char)IAC, (char)DO, (char)cmd};
}

const std::string dont_cmd(const unsigned char cmd) {
  return {(char)IAC, (char)DONT, (char)cmd};
}

uint8_t to_code(char c) {
  uint8_t mask = 0x00ff;
  return c & mask;
}

unsigned short to_printable_code(char c) {
  return (unsigned short)to_code(c);
}

} // namespace iac

namespace shell {

const std::string cursor_to(const uint8_t x, const uint8_t y) {
  std::string cmd = START + '[';
  for (char c : std::to_string(y)) {
    cmd += c;
  }
  cmd += ';';
  for (char c : std::to_string(x)) {
    cmd += c;
  }
  cmd += 'H';
  return cmd;
}

const std::string cursor_up(const uint8_t n) {
  std::string cmd = START + '[';
  for (char c : std::to_string(n)) {
    cmd += c;
  }
  cmd += 'A';
  return cmd;
}

const std::string attr(const Attribute attr) {
  std::string cmd = START + '[';
  for (char c : std::to_string(static_cast<int>(attr))) {
    cmd += c;
  }
  return cmd + 'm';
}

const std::string color(const Color fg_color, const Color bg_color) {
  std::string cmd = START + '[';
  if (bg_color != Color::NONE) {
    cmd += '4';
    for (char c : std::to_string(static_cast<unsigned int>(bg_color))) {
      cmd += c;
    }
  } else {
    cmd += '0';
  }
  cmd += ";3";
  for (char c : std::to_string(static_cast<unsigned int>(fg_color))) {
    cmd += c;
  }
  std::cout << cmd.substr(1) << std::endl;
  return cmd + 'm';
}

} // namespace shell
