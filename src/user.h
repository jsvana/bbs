#pragma once

#include <string>

class User {
 private:
  const std::string username_;
  bool logged_in_ = false;

 public:
  User(const std::string& username) : username_(username) {}

  bool authenticate(const std::string& password);

  bool logged_in() { return logged_in_; }

  void log_out() { logged_in_ = false; }
};
