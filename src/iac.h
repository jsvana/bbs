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

const std::string START = {27};

const std::string CURSOR_TOP_LEFT = START + "[f";

const std::string CLEAR_SCREEN = START + "[2J";
const std::string CLEAR_LINE = START + "[2K";

// Colors
// TODO(jsvana): constexpr generate all colors
// TODO(jsvana): dynamic attributes
const std::string BLACK = START + "[0;30m";
const std::string RED = START + "[0;31m";
const std::string GREEN = START + "[0;32m";
const std::string ORANGE = START + "[0;33m";
const std::string BLUE = START + "[0;34m";
const std::string PURPLE = START + "[0;35m";
const std::string TEAL = START + "[0;36m";
const std::string DEFAULT = START + "[0m";

// Attributes
const std::string BLINK = START + "[5m";
const std::string BOLD = START + "[1m";

const std::string cursor_to(const uint8_t x, const uint8_t y);
const std::string cursor_up(const uint8_t n);

} // namespace shell
