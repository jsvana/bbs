#pragma once

#include "server.h"

class BbsSession : public Session {
 private:
  void handle_line(std::string line);

 public:
  BbsSession(tcp::socket socket) : Session(std::move(socket)) {}
};
