#pragma once

#include "server.h"

class BbsSession : public Session {
 private:
  std::string unfinished_line_;

  uint16_t term_width = 0;
  uint16_t term_height = 0;

  void handle_connect();
  void handle_line(const std::string& line);
  void handle_iac(const std::array<char, max_length>& data, std::size_t bytes);

 public:
  BbsSession(tcp::socket socket) : Session(std::move(socket)) {}
};
