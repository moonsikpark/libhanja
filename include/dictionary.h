// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <string>
#include <unordered_map>

namespace hanja {

using HanjaDictionary = std::unordered_map<std::string, std::string>;

HanjaDictionary load(const std::string& file_path);

}  // namespace hanja

#endif  // DICTIONARY_H_