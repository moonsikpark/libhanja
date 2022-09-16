// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef TYPES_H_
#define TYPES_H_

#include <cstddef>
#include <string>
#include <vector>

namespace hanja {
namespace types {

class Match {
 public:
  Match() = delete;
  Match(const Match&) = delete;
  Match& operator=(const Match&) = delete;
  Match(Match&& p) noexcept = default;
  Match& operator=(Match&& p) = default;

  Match(const std::string& key, const std::string& value,
        const std::vector<std::size_t> pos);

  inline const std::string& get_key() const { return m_key; }

  inline const std::string& get_value() const { return m_value; }

  inline const std::vector<std::size_t>& get_pos() const { return m_pos; }

  inline auto operator<=>(const Match& other) const {
    return this->m_key.length() <=> other.get_key().length();
  }

 private:
  std::string m_key;
  std::string m_value;
  std::vector<std::size_t> m_pos;
};

class MatchPosition {
 public:
  MatchPosition() = delete;
  MatchPosition(const MatchPosition&) = delete;
  MatchPosition& operator=(const MatchPosition&) = delete;
  MatchPosition(MatchPosition&& p) noexcept = default;
  MatchPosition& operator=(MatchPosition&& p) = default;

  MatchPosition(const std::size_t pos, const std::string& value);

  inline const std::size_t get_pos() const { return m_pos; }

  inline const std::string& get_value() const { return m_value; }

  inline auto operator<=>(const MatchPosition& other) const {
    return this->get_pos() <=> other.get_pos();
  }

 private:
  std::string m_value;
  std::size_t m_pos;
};

}  // namespace types
}  // namespace hanja

#endif  // TYPES_H_
