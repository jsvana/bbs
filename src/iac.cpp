#include "iac.h"

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
  std::string cmd = {START, '['};
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
  std::string cmd = {START, '['};
  for (char c : std::to_string(n)) {
    cmd += c;
  }
  cmd += 'A';
  return cmd;
}

} // namespace shell
