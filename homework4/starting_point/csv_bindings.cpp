#include "csv_bindings.hh"

void init_csv_writer_bindings(py::module &m) {
    py::class_<CsvWriter, Compute, std::shared_ptr<CsvWriter>>(m, "CsvWriter")
        .def(py::init<const std::string&>(), py::arg("filename"))
        .def("write", &CsvWriter::write)
        .def("compute", &CsvWriter::compute);
}

PYBIND11_MODULE(csv_writer, m) {
    init_csv_writer_bindings(m);
}