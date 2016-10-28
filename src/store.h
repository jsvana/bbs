#pragma once

#include "rocksdb/db.h"

#include <cassert>

namespace store {

  void init(const std::string& db_path);

  rocksdb::Status get(const std::string& key, std::string& value);

  rocksdb::Status put(const std::string& key, const std::string& value);

} // namespace store
