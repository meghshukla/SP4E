#include "system_evolution.hh"  // For SystemEvolution
#include "gtest/gtest.h"
#include "my_types.hh"
#include "matrix.hh"
#include "particles_factory_interface.hh"  // Include this header for ParticlesFactoryInterface

TEST(TemperatureTest, HomogeneousTemperatureAndNoHeatFlux) {
    // Step 1: Simulate the arguments passed to the main
    Real nsteps = 5000;            // Example number of steps
    int freq = 500;                // Dump frequency
    std::string filename = "dummy.csv";  // Input CSV (not used in the test, but should be passed)
    std::string type = "material_point"; // Particle type
    Real timestep = 0.1;           // Time step
    std::string source = "none";   // Heat source type

    // Step 2: Create SystemEvolution object as per main.cc logic
    // Initialize the factory and create a simulation
    ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();
    SystemEvolution evol(factory.createSimulation(filename, timestep));

    // Set up the simulation parameters
    evol.setNSteps(nsteps);
    evol.setDumpFreq(freq);
    evol.setTemperatureField();
    evol.setHeatSource(source);  // Set the heat source type
    evol.copyTemperatureField(); // Assuming this initializes the temperature field correctly

    // Step 3: Get the temperature and original fields
    System& system = evol.getSystem();
    Matrix<complex>* temperature_field = system.getTemperatureField();
    Matrix<complex>* original_field = system.getHeatSource();  // Assuming original_field comes from heatSource()

    // Step 4: Compare both fields
    for (UInt i = 0; i < temperature_field->size(); i++) {
        for (UInt j = 0; j < temperature_field->size(); j++) {
            ASSERT_NEAR(std::real((*temperature_field)(i, j)), std::real((*original_field)(i, j)), 1e-10);
        }
    }
}
