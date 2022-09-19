// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "dictionary.h"

#include <fstream>
#include <sstream>

namespace hanja {
namespace dictionary {

Dictionary::Dictionary(const compat::string& dictionary_path) noexcept {
  this->init(dictionary_path);
}

void Dictionary::init(const compat::string& dictionary_path) noexcept {
  compat::ifstream fstream;

  // Raise exceptions on failure.
  // fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // TODO: Handle exceptions.
  fstream.open(dictionary_path);

  compat::string line;

  while (std::getline(fstream, line)) {
    compat::string key, value;
    // Skip comments or lines starting with whitespace.
    if (line[0] == kDictionaryComment && line[0] == ' ') {
      continue;
    }

    compat::stringstream ss{line};

    getline(ss, value, kDictionaryDelimiter);
    getline(ss, key, kDictionaryDelimiter);

    m_keys.emplace_back(key);
    m_data.emplace(key, value);
  }
}

}  // namespace dictionary
}  // namespace hanja
