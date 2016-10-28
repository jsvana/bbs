#include "store.h"

namespace store {

  rocksdb::DB* db;

  void init(const std::string& db_path) {
    rocksdb::Options options;
    options.create_if_missing = true;
    auto status = rocksdb::DB::Open(options, db_path, &db);
    assert(status.ok());
  }

  rocksdb::Status get(const std::string& key, std::string& value) {
    return db->Get(rocksdb::ReadOptions(), key, &value);
  }

  rocksdb::Status put(const std::string& key, const std::string& value) {
    return db->Put(rocksdb::WriteOptions(), key, value);
  }

}
