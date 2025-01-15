#ifndef __CSV_BINDINGS__HH__
#define __CSV_BINDINGS__HH__

#include <pybind11/pybind11.h>
#include "csv_writer.hh"

namespace py = pybind11;

void init_csv_writer_bindings(py::module &m);

#endif // __CSV_BINDINGS__HH__