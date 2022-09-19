// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "convert.h"

#include <algorithm>

#include "dictionary.h"
#include "step/suffix_tree.hpp"

namespace hanja {
namespace convert {

Convert::Convert(const compat::string &input,
                 const dictionary::Dictionary &dict) noexcept
    : m_input(input), m_match_changed(input.length(), false) {
  find_match(dict);
}

void Convert::find_match(const dictionary::Dictionary &dict) noexcept {
  // Build a suffix tree.
  step::suffix_tree tree;
  std::copy(m_input.begin(), m_input.end(), std::back_inserter(tree));

  // Find all matching words in a dictionary and save the position.
  for (const auto &key : dict.keys()) {
    std::vector<std::size_t> results;
    tree.find_all(key, std::back_inserter(results));
    if (results.size() > 0) {
      m_match.emplace_back(key, dict.query(key), results);
    }
  }

  // Sort by key descending.
  std::sort(m_match.begin(), m_match.end(), std::greater<types::Match>());

  /* Find MatchPositions using Match array and the input. We need the
   * m_match_changed vector because there are multiple matches that overlap and
   * we don't want them to change the same letter.
   *
   * For two matches "金:김" and "金屬:금속" for a word "金屬", we don't want
   * the both to apply their own pronunciations.
   */
  std::size_t current_pos = 0;

  for (const auto &match : m_match) {
    for (const auto &position : match.get_pos()) {
      // Check if there's an overlap with already changed indexes.
      bool overlap = false;
      for (std::size_t index = position;
           index < position + match.get_key().length(); index++) {
        if (m_match_changed[index]) {
          overlap = true;
          break;
        }
      }

      // Convert the words if there are no overlap.
      if (!overlap) {
        auto value = match.get_value();
        m_match_pos.emplace_back(position, match.get_value());

        // Write the positions we changed to the changed vector.
        for (std::size_t index = position;
             index < position + match.get_key().length(); index++) {
          m_match_changed[index] = true;
        }
      }
    }
  }

  // Sort MatchPositions by position ascending.
  std::sort(m_match_pos.begin(), m_match_pos.end(),
            std::less<types::MatchPosition>());
}

const compat::string Convert::to_korean() const {
  compat::string output{m_input};

  for (const auto &match_position : m_match_pos) {
    output.replace(match_position.get_pos(),
                   match_position.get_value().length(),
                   match_position.get_value());
  }

  return output;
}

const compat::string Convert::to_korean_with_hanja(
    const compat::string &delimiter_start,
    const compat::string &delimiter_end) const {
  compat::string output{m_input};

  std::size_t added_index = 0;

  for (const auto &match_position : m_match_pos) {
    std::size_t current_index = match_position.get_pos() + added_index +
                                match_position.get_value().length();
    output.insert(current_index, delimiter_start);

    current_index += delimiter_start.length();
    output.insert(current_index, match_position.get_value());

    current_index += match_position.get_value().length();
    output.insert(current_index, delimiter_end);

    added_index += match_position.get_value().length() +
                   delimiter_start.length() + delimiter_end.length();
  }

  return output;
}

}  // namespace convert
}  // namespace hanja
