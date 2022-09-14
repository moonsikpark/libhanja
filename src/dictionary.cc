// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "dictionary.h"

#include <fstream>
#include <sstream>

namespace hanja {

HanjaDictionary load(const std::string& file_path) {
  HanjaDictionary result;

  std::ifstream file(file_path);

  // TODO: enable use of comment characters.
  // TODO: specify format.

  if (file.is_open()) {
    std::string line{""};
    while (std::getline(file, line)) {
      std::string key, value;
      std::stringstream ss(line);

      getline(ss, value, ':');
      getline(ss, key, ':');

      result.insert({key, value});
    }
    file.close();
  }

  return result;
}

}  // namespace hanja