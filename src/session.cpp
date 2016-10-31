#include "session.h"

#include <vector>

void BbsSession::enable_client_echo() {
  write({(char)iac::IAC, (char)iac::WONT, (char)iac::CECHO});
}

void BbsSession::disable_client_echo() {
  write({(char)iac::IAC, (char)iac::WILL, (char)iac::CECHO});
}

void BbsSession::reset_line() {
  write("\r" + shell::CLEAR_LINE);
}

void BbsSession::handle_connect() {
  write({(char)iac::IAC, (char)iac::DO, (char)iac::NAWS});

  write_template("../src/templates/index.scr", {});
}

void BbsSession::read_line(const std::string& line) {
  unfinished_line_ += line;
  auto end = unfinished_line_.find("\r\n");
  if (end != std::string::npos) {
    std::string line = unfinished_line_.substr(0, end);
    unfinished_line_ = unfinished_line_.substr(end + 2);
    handle_line(line);
  }
}

void BbsSession::prompt_password() {
  write(shell::BOLD);
  write("Password: ");
  write(shell::DEFAULT);
  disable_client_echo();
}

void BbsSession::handle_line(const std::string& line) {
  switch (state_) {
  case BbsState::WAITING_NAME:
    state_ = BbsState::WAITING_PASSWORD;
    user_ = std::make_unique<User>(line);
    prompt_password();
    break;

  case BbsState::WAITING_PASSWORD:
    if (user_->authenticate(line)) {
      state_ = BbsState::LOGGED_IN;

      write(shell::CLEAR_SCREEN);
      write(shell::cursor_to(5, 5));
      write("Logged in");
    } else {
      write("\r\nIncorrect password\r\n");
      prompt_password();
    }
    break;
  };
}

void BbsSession::handle_iac(const std::array<char, max_length>& data, std::size_t bytes) {
  std::size_t i = 0;
  while (i < bytes) {
    unsigned char c = data[i];
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
