#include "session.h"

void BbsSession::handle_line(std::string line) {
  std::cout << "[RECV] " << line << std::endl;
}
