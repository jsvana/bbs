#pragma once

#include <cinttypes>
#include <string>

namespace iac {

const unsigned char IS = 0;          // Sub-negotiation IS command

// Apparently ECHO is reserved so we use CECHO
const unsigned char CECHO = 1;

const unsigned char MOVE_CURSOR = 5; // Moves cursor to point
const unsigned char DET = 20;        // Data Entry Terminal extensions

const unsigned char NAWS = 31;       // Window size option

const unsigned char SE = 240;        // The end of sub-negotiation options
const unsigned char NOP = 241;       // No operation
const unsigned char SB = 250;        // The start of sub-negotiation options

const unsigned char WILL = 251;      // Confirm willingness to negotiate
const unsigned char WONT = 252;      // Confirm unwillingness to negotiate
const unsigned char DO = 253;        // Indicate willingness to negotiate
const unsigned char DONT = 254;      // Indicate unwillingness to negotiate
const unsigned char IAC = 255;       // Marks the start of a negotiation sequence

const std::string do_cmd(const unsigned char cmd);
const std::string dont_cmd(const unsigned char cmd);

uint8_t to_code(char c);
unsigned short to_printable_code(char c);

} // namespace iac

namespace shell {

const std::string BLOCK = "\u2588";

const std::string START = {27};

const std::string CURSOR_TOP_LEFT = START + "[f";

const std::string CLEAR_SCREEN = START + "[2J";
const std::string CLEAR_LINE = START + "[2K";

enum class Color : int {
  NONE = -1,

  BLACK = 0,
  RED = 1,
  GREEN = 2,
  YELLOW = 3,
  BLUE = 4,
  MAGENTA = 5,
  CYAN = 6,
  WHITE = 7,
};

enum class Attribute : unsigned int {
  NONE = 0,
  BOLD = 1,
  BLINK = 5,
};

const std::string cursor_to(const uint8_t x, const uint8_t y);
const std::string cursor_up(const uint8_t n);

const std::string attr(const Attribute attr);

const std::string color(const Color fg_color, const Color bg_color = Color::NONE);

} // namespace shell
