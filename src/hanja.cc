// Copyright (c) 2022 ESTsoft Corp. All rights reserved.

#include "hanja.h"

#include <execution>
#include <mutex>

#include "dictionary.h"
#include "step/suffix_tree.hpp"

namespace hanja {

std::string find_match(const std::string &input) {
  HanjaDictionary dict = load("hanja.txt");

  std::vector<std::string> patterns;

  for (const auto &[key, _] : dict) {
    patterns.push_back(key);
  }

  step::suffix_tree tree{};
  std::vector<std::pair<std::string, std::vector<std::size_t>>> matches;
  std::mutex hold;

  std::copy(input.begin(), input.end(), std::back_inserter(tree));

  std::for_each(std::execution::par_unseq, patterns.begin(), patterns.end(),
                [&tree, &matches, &hold](const std::string &val) {
                  std::vector<std::size_t> results;
                  tree.find_all(val, std::back_inserter(results));
                  if (results.size() != 0) {
                    const std::lock_guard<std::mutex> lock(hold);
                    matches.push_back(std::make_pair(val, results));
                  }
                });

  std::sort(matches.begin(), matches.end(),
            [](const std::pair<std::string, std::vector<std::size_t>> &a,
               const std::pair<std::string, std::vector<std::size_t>> &b) {
              return a.first.size() > b.first.size();
            });

  std::string result{input};
  std::vector<bool> changed(result.length(), false);

  std::vector<std::pair<std::string, std::vector<std::size_t>>>::iterator it;

  for (it = matches.begin(); it != matches.end(); it++) {
    std::for_each(it->second.begin(), it->second.end(),
                  [&result, &it, &changed, &dict](const std::size_t pos) {
                    for (size_t i = pos; i < pos + it->first.length(); i++) {
                      if (changed[i]) {
                        return;
                      }
                    }

                    result.replace(pos, it->first.length(), dict[it->first]);
                    for (size_t i = pos; i < pos + it->first.length(); i++) {
                      changed[i] = true;
                    }
                  });
  }
  return result;
}

}  // namespace hanja
