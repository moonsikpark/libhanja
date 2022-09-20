// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef CONVERT_H_
#define CONVERT_H_

#include <string>
#include <vector>

#include "dictionary.h"
#include "types.h"

namespace hanja {
namespace convert {

class Convert {
 public:
  Convert() = delete;
  Convert(const Convert&) = delete;
  Convert& operator=(const Convert&) = delete;
  Convert(const compat::string& input,
          const dictionary::Dictionary& dict) noexcept;

  const compat::string to_korean() const;

  const compat::string to_korean_with_hanja(
      const compat::string& delimiter_start,
      const compat::string& delimiter_end) const;

  inline const compat::string input() const { return m_input; }

 private:
  void find_match(const dictionary::Dictionary& dict) noexcept;
  const compat::string m_input;
  std::vector<types::Match> m_match;
  std::vector<bool> m_match_changed;
  std::vector<types::MatchPosition> m_match_pos;
};

}  // namespace convert
}  // namespace hanja

#endif  // CONVERT_H_
