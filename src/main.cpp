#include "server.h"
#include "session.h"
#include "store.h"

#include <iostream>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <port>\n";
    return 1;
  }

  store::init("testdb");

  BbsServer<BbsSession> server(std::atoi(argv[1]));

  server.run();

  return 0;
}
