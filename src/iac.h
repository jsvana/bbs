#pragma once

#include <cinttypes>
#include <string>

namespace iac {

const unsigned char IS = 0;          // Sub-negotiation IS command
const unsigned char SEND = 1;        // Sub-negotiation SEND command

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

const char START = 27;

const std::string CURSOR_TOP_LEFT = {START, '[', 'f'};

const std::string CLEAR_SCREEN = {START, '[', '2', 'J'};
const std::string CLEAR_LINE = {START, '[', '2', 'K'};

// Colors
const std::string GREEN = {START, '[', '0', ';', '3', '2', 'm'};
const std::string DEFAULT = {START, '[', '0', 'm'};

// Attributes
const std::string BLINK = {START, '[', '5', 'm'};
const std::string BOLD = {START, '[', '1', 'm'};

const std::string cursor_to(const uint8_t x, const uint8_t y);

} // namespace shell
