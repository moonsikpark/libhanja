// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"

namespace hanja {
namespace dictionary {

constexpr char kDictionaryDelimiter = ':';
constexpr char kDictionaryComment = '#';

class Dictionary {
 public:
  Dictionary() = delete;
  Dictionary(const Dictionary&) = delete;
  Dictionary& operator=(const Dictionary&) = delete;
  Dictionary(const std::string& dictionary_path);

  inline const std::vector<std::string>& keys() const { return m_keys; }

  // TODO: handle exception when querying non-existant keys
  inline const std::string& query(const std::string& key) const {
    return m_data.at(key);
  }

 private:
  void init(const std::string& dictionary_path);
  std::unordered_map<std::string, std::string> m_data;
  std::vector<std::string> m_keys;
};

}  // namespace dictionary
}  // namespace hanja

#endif  // DICTIONARY_H_
