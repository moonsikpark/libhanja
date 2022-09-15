// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "types.h"

namespace hanja {
namespace types {

Match::Match(const std::string& key, const std::string& value,
             const std::vector<std::size_t> pos)
    : m_key(key), m_value(value), m_pos(pos) {}

}  // namespace types
}  // namespace hanja
