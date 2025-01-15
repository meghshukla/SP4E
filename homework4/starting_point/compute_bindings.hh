#ifndef __COMPUTE_BINDINGS__HH__
#define __COMPUTE_BINDINGS__HH__

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "compute.hh"
#include "compute_boundary.hh"
#include "compute_contact.hh"
#include "compute_energy.hh"
#include "compute_gravity.hh"
#include "compute_interaction.hh"
#include "compute_kinetic_energy.hh"
#include "compute_potential_energy.hh"
#include "compute_temperature_finite_differences.hh"
#include "compute_temperature.hh"
#include "compute_verlet_integration.hh"

namespace py = pybind11;

void init_bindings(py::module &m);

#endif // __COMPUTE_BINDINGS__HH__