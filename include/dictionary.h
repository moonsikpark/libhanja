// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"

namespace hanja {
namespace dictionary {

class DictionaryItem {
 public:
  DictionaryItem() = delete;
  DictionaryItem(const DictionaryItem&) = default;
  DictionaryItem& operator=(const DictionaryItem&) = default;
  DictionaryItem(DictionaryItem&& p) noexcept = default;
  DictionaryItem& operator=(DictionaryItem&& p) = default;

  DictionaryItem(const compat::string& key,
                 const compat::string& value) noexcept;

  inline const compat::string& get_key() const { return m_key; }

  inline const compat::string& get_value() const { return m_value; }

  inline types::MatchPosition to_match_position(const std::size_t pos) const {
    return types::MatchPosition(pos, m_key, m_value);
  }

  // BUG: in case of unicode 4 byte letter vs 3 byte letter
  inline auto operator<=>(const DictionaryItem& other) const {
    return this->get_key().length() <=> other.get_key().length();
  }

 private:
  compat::string m_key;
  compat::string m_value;
};

constexpr char kDictionaryDelimiter = ':';
constexpr char kDictionaryComment = '#';

class Dictionary {
 public:
  Dictionary() noexcept = default;
  Dictionary(const Dictionary&) = delete;
  Dictionary& operator=(const Dictionary&) = delete;

  void add_data(const compat::string& dictionary_path);

  // Warning: std::ranges are not compatable with pybind11.
  inline auto keys() const { return std::ranges::views::keys(m_data); }

  inline const std::size_t size() const { return m_data.size(); }

  // TODO: handle exception when querying non-existant keys
  inline const DictionaryItem& query(const compat::string& key) const {
    return m_data.at(key);
  }

 private:
  // Note: Using unordered_map<string, string> speeds up about 4x.
  std::unordered_map<compat::string, DictionaryItem> m_data;
};

}  // namespace dictionary
}  // namespace hanja

#endif  // DICTIONARY_H_
