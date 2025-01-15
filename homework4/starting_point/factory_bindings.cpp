#include "factory_bindings.hh"

namespace py = pybind11;

void init_bindings(py::module &m) {
    py::class_<ParticlesFactoryInterface, std::shared_ptr<ParticlesFactoryInterface>>(m, "ParticlesFactoryInterface")
        .def("createSimulation", [](ParticlesFactoryInterface &self, const std::string &fname, Real timestep, py::function func) {
            self.createSimulation(fname, timestep, func);
        }) 
        .def_static("getInstance", &ParticlesFactoryInterface::getInstance, py::return_value_policy::reference)
        .def("getSystemEvolution", &ParticlesFactoryInterface::getSystemEvolution, py::return_value_policy::reference);

    py::class_<MaterialPointsFactory, ParticlesFactoryInterface, std::shared_ptr<MaterialPointsFactory>>(m, "MaterialPointsFactory")
        .def_static("getInstance", &MaterialPointsFactory::getInstance, py::return_value_policy::reference)
        .def("createSimulation", &MaterialPointsFactory::createSimulation)
        .def("createDefaultComputes", &MaterialPointsFactory::createDefaultComputes, py::arg("timestep"))
        .def("createParticle", &MaterialPointsFactory::createParticle);

    py::class_<PlanetsFactory, ParticlesFactoryInterface, std::shared_ptr<PlanetsFactory>>(m, "PlanetsFactory")
        .def_static("getInstance", &PlanetsFactory::getInstance, py::return_value_policy::reference)
        .def("createSimulation", &PlanetsFactory::createSimulation)
        .def("createDefaultComputes", &PlanetsFactory::createDefaultComputes, py::arg("timestep"))
        .def("createParticle", &PlanetsFactory::createParticle);

    py::class_<PingPongBallsFactory, ParticlesFactoryInterface, std::shared_ptr<PingPongBallsFactory>>(m, "PingPongBallsFactory")
        .def_static("getInstance", &PingPongBallsFactory::getInstance, py::return_value_policy::reference)
        .def("createSimulation", &PingPongBallsFactory::createSimulation)
        .def("createParticle", &PingPongBallsFactory::createParticle);
}

PYBIND11_MODULE(PyFactory, m) {
    init_bindings(m);
}