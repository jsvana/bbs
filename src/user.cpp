#include "user.h"

#include "store.h"

#include <iostream>

bool User::authenticate(const std::string& password) {
  std::string pass;
  store::get(username_, pass);

  if (pass == password) {
    logged_in_ = true;
  }

  return logged_in_;
}
