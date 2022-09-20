// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include "types.h"

namespace hanja {
namespace types {

Match::Match(const compat::string& key, const compat::string& value,
             const std::vector<std::size_t> pos)
    : m_key(key), m_value(value), m_pos(pos) {}

MatchPosition::MatchPosition(const std::size_t pos, const compat::string& value)
    : m_pos(pos), m_value(value) {}

}  // namespace types
}  // namespace hanja
