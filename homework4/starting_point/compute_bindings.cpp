#include "compute_bindings.hh"

void init_bindings(py::module &m) {
    py::class_<Compute, std::shared_ptr<Compute>>(m, "Compute")
        .def("compute", &Compute::compute);

    py::class_<ComputeInteraction, Compute, std::shared_ptr<ComputeInteraction>>(m, "ComputeInteraction")
        .def(py::init<>())
        .def("applyOnPairs", [](ComputeInteraction &self, py::function func, System &system) {
            self.applyOnPairs(func, system);
        });

    py::class_<ComputeGravity, ComputeInteraction, std::shared_ptr<ComputeGravity>>(m, "ComputeGravity")
        .def(py::init<>())
        .def("compute", &ComputeGravity::compute)
        .def("setG", &ComputeGravity::setG);

    py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(m, "ComputeTemperature")
        .def(py::init<>())
        .def("compute", &ComputeTemperature::compute)
        .def_property("conductivity", &ComputeTemperature::getConductivity, &ComputeTemperature::getConductivity)
        .def_property("capacity", &ComputeTemperature::getCapacity, &ComputeTemperature::getCapacity)
        .def_property("density", &ComputeTemperature::getDensity, &ComputeTemperature::getDensity)
        .def_property("L", &ComputeTemperature::getL, &ComputeTemperature::getL)
        .def_property("delta_t", &ComputeTemperature::getDeltat, &ComputeTemperature::getDeltat)
        .def_readwrite("implicit", &ComputeTemperature::implicit);

    py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(m, "ComputeVerletIntegration")
        .def(py::init<Real>())
        .def("compute", &ComputeVerletIntegration::compute)
        .def("setDeltaT", &ComputeVerletIntegration::setDeltaT)
        .def("addInteraction", &ComputeVerletIntegration::addInteraction);
}

PYBIND11_MODULE(PyCompute, m) {
    init_bindings(m);
}