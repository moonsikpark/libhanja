// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "hanja.h"

#include "dictionary.h"
#include "scoped_timer.h"
#include "step/suffix_tree.hpp"

namespace hanja {
namespace convert {

Convert::Convert(const std::string &input, const dictionary::Dictionary &dict)
    : m_input(input) {
  find_match(dict);
}

void Convert::find_match(const dictionary::Dictionary &dict) {
  // Build a suffix tree.
  step::suffix_tree tree;
  std::copy(m_input.begin(), m_input.end(), std::back_inserter(tree));

  // Find all matching words in a dictionary and save the position.
  for (const auto &key : dict.keys()) {
    std::vector<std::size_t> results;
    tree.find_all(key, std::back_inserter(results));
    if (results.size() > 0) {
      m_match_key_value_positions.emplace(
          key, std::make_pair(dict.query(key), results));
    }
  }
}

const std::string Convert::to_string() const {
  std::string output{m_input};

  /* We need the changed vector because there are multiple matches that overlap
   * and we don't want them to change the same letter.
   *
   * For two matches "金:김" and "金屬:금속" for a word "金屬", we don't want
   * the both to apply their own pronunciations.
   */
  std::vector<bool> changed(output.length(), false);

  for (const auto &[key, v] : m_match_key_value_positions) {
    for (const auto &position : v.second) {
      // Check if there's an overlap with already changed indexes.
      bool overlap = false;
      for (std::size_t index = position; index < position + key.length();
           index++) {
        if (changed[index]) {
          overlap = true;
          break;
        }
      }

      // Convert the words if there are no overlap.
      if (!overlap) {
        auto value = v.first;
        output.replace(position, key.length(), value);

        // Write the positions we changed to the changed vector.
        for (std::size_t index = position; index < position + key.length();
             index++) {
          changed[index] = true;
        }
      }
    }
  }

  return output;
}

}  // namespace convert
}  // namespace hanja
