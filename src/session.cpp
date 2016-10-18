#include "session.h"

#include <vector>

void BbsSession::handle_connect() {
  write({(char)iac::IAC, (char)iac::DO, (char)iac::NAWS});

  write(shell::CLEAR_SCREEN);
  write(shell::CURSOR_TOP_LEFT);
  write(shell::GREEN);
	std::vector<std::string> welcome = {
		{"                     ^    ^                                            "},
		{"                    / \\  //\\                                         "},
		{"      |\\___/|      /   \\//  .\\                                      "},
		{"      /O  O  \\__  /    //  | \\ \\                                    "},
		{"     /     /  \\/_/    //   |  \\  \\                                  "},
		{"     @___@'    \\/_   //    |   \\   \\                                "},
		{"        |       \\/_ //     |    \\    \\                              "},
		{"        |        \\///      |     \\     \\                            "},
		{"       _|_ /   )  //       |      \\     _\\                           "},
		{"      '/,_ _ _/  ( ; -.    |    _ _\\.-~        .-~~~^-.               "},
		{"      ,-{        _      `-.|.-~-.           .~         `.              "},
		{"       '/\\      /                 ~-. _ .-~      .-~^-.  \\           "},
		{"          `.   {            }                   /      \\  \\          "},
		{"        .----~-.\\        \\-'                 .~         \\  `. \\^-. "},
		{"       ///.----..>    c   \\             _ -~             `.  ^-`   ^-_"},
		{"         ///-._ _ _ _ _ _ _}^ - - - - ~                     ~--,   .-~ "},
		{"                                                              /.-'     "},
	};

	for (const auto& line : welcome) {
    write(line + "\n");
  }
  write(shell::DEFAULT);

  write(shell::BOLD);
  write("     Name: ");
  write(shell::DEFAULT);
}

void BbsSession::handle_line(const std::string& line) {
  std::cout << "[RECV] " << line << std::endl;
  unfinished_line_ += line;
  for (unsigned char c : unfinished_line_) {
    std::cout << iac::to_printable_code(c) << " ";
  }
  std::cout << std::endl;
  auto end = unfinished_line_.find("\n");
  if (end != std::string::npos) {
    std::string line = unfinished_line_.substr(0, end);
    unfinished_line_ = unfinished_line_.substr(end + 1);
    handle_line(line);
  }
}

void BbsSession::handle_iac(const std::array<char, max_length>& data, std::size_t bytes) {
  std::size_t i = 0;
  //int sb_count = 0;
  while (i < bytes) {
    unsigned char c = data[i];
    //std::cout << "CHAR " << (unsigned short)iac::to_code(c) << std::endl;
    if (c == iac::WILL || c == iac::WONT || c == iac::DO || c == iac::DONT) {
      std::cout << "Client ";
      switch (c) {
      case iac::WILL:
        std::cout << "will";
        break;
      case iac::WONT:
        std::cout << "will not";
        break;
      case iac::DO:
        std::cout << "does";
        if (data[i + 1] == 6) {
          // Quit on ^C
          running_ = false;
        }
        break;
      case iac::DONT:
        std::cout << "does not";
        break;
      }
      std::cout << " " << iac::to_printable_code(data[i + 1]) << std::endl;
      ++i;
    } else if (c == iac::SB) {
      ++i;
      std::cout << "Beginning SB for " << iac::to_printable_code(data[i]) << std::endl;

      ++i;
      term_width = (data[i] << 8) | data[i + 1];

      i += 2;
      term_height = (data[i] << 8) | data[i + 1];

      i += 2;

      std::cout << "Term dimensions: (" << term_width << ", " << term_height << ")" << std::endl;
    }
    ++i;
  }
}
