// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "convert.h"
#include "dictionary.h"

namespace py = pybind11;

PYBIND11_MODULE(pyhanja, m) {
  py::class_<hanja::dictionary::DictionaryItem>(m, "DictionaryItem")
      .def_property_readonly("key", &hanja::dictionary::DictionaryItem::get_key)
      .def_property_readonly("value",
                             &hanja::dictionary::DictionaryItem::get_value);

  py::class_<hanja::dictionary::Dictionary>(m, "Dictionary")
      .def(py::init<const hanja::compat::string &>())
      .def("query", &hanja::dictionary::Dictionary::query)
      .def_property_readonly("size", &hanja::dictionary::Dictionary::size);

  py::class_<hanja::convert::Convert>(m, "Convert")
      .def(py::init<const hanja::compat::string &,
                    const hanja::dictionary::Dictionary &>())
      .def("to_korean", &hanja::convert::Convert::to_korean)
      .def("to_korean_with_hanja",
           &hanja::convert::Convert::to_korean_with_hanja)
      .def_property_readonly("match_pos",
                             &hanja::convert::Convert::get_match_pos);

  py::class_<hanja::types::MatchPosition>(m, "MatchPosition")
      .def_property_readonly("pos", &hanja::types::MatchPosition::get_pos)
      .def_property_readonly("key", &hanja::types::MatchPosition::get_key)
      .def_property_readonly("value", &hanja::types::MatchPosition::get_value);
}
