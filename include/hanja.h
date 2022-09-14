// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#ifndef HANJA_H_
#define HANJA_H_
#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "dictionary.h"

namespace hanja {

std::string find_match(const std::string &input);

}  // namespace hanja

#endif  // HANJA_H_