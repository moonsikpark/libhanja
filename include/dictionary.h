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
  Dictionary(const compat::string& dictionary_path) noexcept;

  inline const std::vector<compat::string>& keys() const { return m_keys; }

  inline const std::size_t length() const { return m_keys.size(); }

  // TODO: handle exception when querying non-existant keys
  inline const compat::string& query(const compat::string& key) const {
    return m_data.at(key);
  }

 private:
  void init(const compat::string& dictionary_path) noexcept;
  std::unordered_map<compat::string, compat::string> m_data;
  std::vector<compat::string> m_keys;
};

}  // namespace dictionary
}  // namespace hanja

#endif  // DICTIONARY_H_
