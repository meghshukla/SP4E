#ifndef __FACTORY_BINDINGS__HH__
#define __FACTORY_BINDINGS__HH__

#include <pybind11/pybind11.h>
#include "particles_factory_interface.hh"
#include "material_points_factory.hh"
#include "planets_factory.hh"
#include "ping_pong_balls_factory.hh"

namespace py = pybind11;

void init_bindings(py::module &m);

#endif // __FACTORY_BINDINGS__HH__