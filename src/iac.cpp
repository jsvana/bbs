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
  // Attempt at RFC1043. Doesn't appear to work (client responds IAC WONT DET).
  return {(char)iac::IAC, (char)iac::SB, (char)iac::DET, (char)iac::MOVE_CURSOR, (char)y, (char)x, (char)iac::IAC, (char)iac::SE};
}

} // namespace shell
