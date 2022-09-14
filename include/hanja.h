// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef HANJA_H_
#define HANJA_H_

#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "dictionary.h"

namespace hanja {
namespace convert {

class Convert {
 public:
  Convert() = delete;
  Convert(const Convert&) = delete;
  Convert& operator=(const Convert&) = delete;
  Convert(const std::string& input, const dictionary::Dictionary& dict);
  // TODO: Specify options of exporting to string.
  const std::string to_string() const;

 private:
  void find_match(const dictionary::Dictionary& dict);
  const std::string m_input;
  std::map<std::string, std::pair<std::string, std::vector<std::size_t>>,
           std::greater<std::string>>
      m_match_key_value_positions;
};

}  // namespace convert
}  // namespace hanja

#endif  // HANJA_H_
