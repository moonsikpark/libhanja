// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "dictionary.h"

#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <locale>
#endif

namespace hanja {
namespace dictionary {

DictionaryItem::DictionaryItem(const compat::string& key,
                               const compat::string& value) noexcept
    : m_key(key), m_value(value) {}

void Dictionary::add_data(const compat::string& dictionary_path) {
#ifdef _WIN32
  std::locale::global(std::locale(".UTF-8"));
#endif
  compat::ifstream fstream;

  // Raise exceptions on failure.
  // fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // TODO: Handle exceptions.
  fstream.open(dictionary_path);

  compat::string line;

  while (std::getline(fstream, line)) {
    compat::string key, value;
    // Skip comments or lines starting with whitespace.
    if (line[0] == kDictionaryComment || line[0] == ' ') {
      continue;
    }

    compat::stringstream ss{line};

    getline(ss, value, (compat::char_t)kDictionaryDelimiter);
    getline(ss, key, (compat::char_t)kDictionaryDelimiter);

    if (!key.empty()) {
      m_data.emplace(key, DictionaryItem(key, value));
    }
  }
}

}  // namespace dictionary
}  // namespace hanja
