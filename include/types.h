// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef TYPES_H_
#define TYPES_H_

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace hanja {

namespace compat {
#ifdef _WIN32
using string = std::wstring;
using ifstream = std::wifstream;
using stringstream = std::wstringstream;
using char_t = wchar_t;
#else
using string = std::string;
using ifstream = std::ifstream;
using stringstream = std::stringstream;
using char_t = char;
#endif
}  // namespace compat

namespace types {

class Match {
 public:
  Match() = delete;
  Match(const Match&) = delete;
  Match& operator=(const Match&) = delete;
  Match(Match&& p) noexcept = default;
  Match& operator=(Match&& p) = default;

  Match(const compat::string& key, const compat::string& value,
        const std::vector<std::size_t> pos);

  inline const compat::string& get_key() const { return m_key; }

  inline const compat::string& get_value() const { return m_value; }

  inline const std::vector<std::size_t>& get_pos() const { return m_pos; }

  inline auto operator<=>(const Match& other) const {
    return this->m_key.length() <=> other.get_key().length();
  }

 private:
  compat::string m_key;
  compat::string m_value;
  std::vector<std::size_t> m_pos;
};

class MatchPosition {
 public:
  MatchPosition() = delete;
  MatchPosition(const MatchPosition&) = delete;
  MatchPosition& operator=(const MatchPosition&) = delete;
  MatchPosition(MatchPosition&& p) noexcept = default;
  MatchPosition& operator=(MatchPosition&& p) = default;

  MatchPosition(const std::size_t pos, const compat::string& value);

  inline const std::size_t get_pos() const { return m_pos; }

  inline const compat::string& get_value() const { return m_value; }

  inline auto operator<=>(const MatchPosition& other) const {
    return this->get_pos() <=> other.get_pos();
  }

 private:
  compat::string m_value;
  std::size_t m_pos;
};

}  // namespace types
}  // namespace hanja

#endif  // TYPES_H_
