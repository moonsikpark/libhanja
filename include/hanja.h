// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef HANJA_H_
#define HANJA_H_

#include <cstddef>
#include <map>
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
  Convert(const std::string& input, const dictionary::Dictionary& dict);

  const std::string to_korean() const;

  const std::string to_korean_with_hanja(
      const std::string& delimiter_start,
      const std::string& delimiter_end) const;

  inline const std::string input() const { return m_input; }

 private:
  void find_match(const dictionary::Dictionary& dict);
  const std::string m_input;
  std::vector<types::Match> m_match;
};

}  // namespace convert
}  // namespace hanja

#endif  // HANJA_H_
