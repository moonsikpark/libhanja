// Copyright (c) 2022 ESTsoft Corp. All rights reserved.
#include <pybind11/pybind11.h>

#include "convert.h"
#include "dictionary.h"

namespace py = pybind11;

PYBIND11_MODULE(pyhanja, m) {
  py::class_<hanja::dictionary::Dictionary>(m, "Dictionary")
      .def(py::init<const hanja::compat::string &>())
      .def("query", &hanja::dictionary::Dictionary::query)
      .def("size", &hanja::dictionary::Dictionary::length);
  py::class_<hanja::convert::Convert>(m, "Convert")
      .def(py::init<const hanja::compat::string &,
                    const hanja::dictionary::Dictionary &>())
      .def("to_korean", &hanja::convert::Convert::to_korean)
      .def("to_korean_with_hanja",
           &hanja::convert::Convert::to_korean_with_hanja);
}