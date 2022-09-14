// Copyright (c) 2022 ESTsoft Corp. All rights reserved.

#include "hanja.h"

#include <execution>
#include <mutex>

#include "step/suffix_tree.hpp"

namespace hanja {

std::map<std::string, std::vector<std::size_t>> find_match(
    const std::string &input) {
  HanjaDictionary dict = load("hanja.txt");

  std::vector<std::string> patterns;

  for (const auto &[key, _] : dict) {
    patterns.push_back(key);
  }

  step::suffix_tree tree{};
  std::map<std::string, std::vector<std::size_t>> matches;
  std::mutex hold;

  std::copy(input.begin(), input.end(), std::back_inserter(tree));

  std::for_each(std::execution::par_unseq, patterns.begin(), patterns.end(),
                [&tree, &matches, &hold](const std::string &val) {
                  std::vector<std::size_t> results;
                  tree.find_all(val, std::back_inserter(results));
                  if (results.size() != 0) {
                    const std::lock_guard<std::mutex> lock(hold);
                    matches.insert({val, results});
                  }
                });

  return matches;
}

}  // namespace hanja
