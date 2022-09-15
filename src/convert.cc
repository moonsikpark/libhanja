// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "convert.h"

#include "dictionary.h"
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
      m_match.emplace_back(key, dict.query(key), results);
    }
  }

  // Sort by key descending.
  std::sort(m_match.begin(), m_match.end(), std::greater<types::Match>());
}

const std::string Convert::to_korean() const {
  std::string output{m_input};

  /* We need the changed vector because there are multiple matches that overlap
   * and we don't want them to change the same letter.
   *
   * For two matches "金:김" and "金屬:금속" for a word "金屬", we don't want
   * the both to apply their own pronunciations.
   */
  std::vector<bool> changed(m_input.length(), false);

  for (const auto &match : m_match) {
    for (const auto &position : match.get_pos()) {
      // Check if there's an overlap with already changed indexes.
      bool overlap = false;
      for (std::size_t index = position;
           index < position + match.get_key().length(); index++) {
        if (changed[index]) {
          overlap = true;
          break;
        }
      }

      // Convert the words if there are no overlap.
      if (!overlap) {
        auto value = match.get_value();
        output.replace(position, match.get_key().length(), value);

        // Write the positions we changed to the changed vector.
        for (std::size_t index = position;
             index < position + match.get_key().length(); index++) {
          changed[index] = true;
        }
      }
    }
  }

  return output;
}
const std::string Convert::to_korean_with_hanja(
    const std::string &delimiter_start,
    const std::string &delimiter_end) const {
  std::string output{m_input};
  /* We need the changed vector because there are multiple matches that overlap
   * and we don't want them to change the same letter.
   *
   * For two matches "金:김" and "金屬:금속" for a word "金屬", we don't want
   * the both to apply their own pronunciations.
   */
  std::vector<bool> changed(m_input.length(), false);

  std::size_t current_pos = 0;
  std::vector<std::pair<std::size_t, std::string>> v1;

  for (const auto &match : m_match) {
    for (const auto &position : match.get_pos()) {
      // Check if there's an overlap with already changed indexes.
      bool overlap = false;
      for (std::size_t index = position;
           index < position + match.get_key().length(); index++) {
        if (changed[index]) {
          overlap = true;
          break;
        }
      }

      // Convert the words if there are no overlap.
      if (!overlap) {
        auto value = match.get_value();
        v1.emplace_back(position, match.get_value());

        // Write the positions we changed to the changed vector.
        for (std::size_t index = position;
             index < position + match.get_key().length(); index++) {
          changed[index] = true;
        }
      }
    }
  }

  std::sort(v1.begin(), v1.end(),
            [](const std::pair<std::size_t, std::string> &a,
               const std::pair<std::size_t, std::string> &b) {
              return a.first < b.first;
            });

  std::size_t added_index = 0;

  for (auto &v : v1) {
    output.insert(v.first + added_index + v.second.length(), delimiter_start);
    output.insert(
        v.first + added_index + v.second.length() + delimiter_start.length(),
        v.second);
    output.insert(v.first + added_index + v.second.length() +
                      delimiter_start.length() + v.second.length(),
                  delimiter_end);
    added_index +=
        v.second.length() + delimiter_start.length() + delimiter_end.length();
  }

  return output;
}
}  // namespace convert
}  // namespace hanja
