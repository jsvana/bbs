#pragma once

#include "server.h"

#include "user.h"

#include <memory>

enum class BbsState {
  WAITING_NAME,
  WAITING_PASSWORD,
  LOGGED_IN,
};

class BbsSession : public Session {
 private:
  std::string unfinished_line_;

  std::unique_ptr<User> user_;

  BbsState state_ = BbsState::WAITING_NAME;

  uint16_t term_width = 0;
  uint16_t term_height = 0;

  void enable_client_echo();
  void disable_client_echo();
  void reset_line();
  void prompt_password();

  void handle_connect();
  void read_line(const std::string& line);
  void handle_line(const std::string& line);
  void handle_iac(const std::array<char, max_length>& data, std::size_t bytes);

 public:
  BbsSession(tcp::socket socket) : Session(std::move(socket)) {}
};
