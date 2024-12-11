#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "my_types.hh"
#include "ping_pong_balls_factory.hh"
#include "material_points_factory.hh"
#include "planets_factory.hh"
#include "system.hh"
/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <iostream>
#include <sstream>
/* -------------------------------------------------------------------------- */

int main(int argc, char** argv) {
  if (argc != 7) {
    std::cout << "Usage: " << argv[0]
              << " nsteps dump_freq input.csv particle_type timestep heat_source"
              << std::endl;
    std::cout << "\tparticle type can be: planet, ping_pong, material_point" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // the number of steps to perform
  Real nsteps;
  std::stringstream(argv[1]) >> nsteps;
  // freq to dump
  int freq;
  std::stringstream(argv[2]) >> freq;
  // init file
  std::string filename = argv[3];
  // particle type
  std::string type = argv[4];
  // timestep
  Real timestep;
  std::stringstream(argv[5]) >> timestep;
  // heat source
  std::string source = argv[6];

  if (type == "planet")
    PlanetsFactory::getInstance();
  else if (type == "ping_pong")
    PingPongBallsFactory::getInstance();
  else if (type == "material_point")
    MaterialPointsFactory::getInstance();  
  else {
    std::cout << "Unknown particle type: " << type << std::endl;
    std::exit(EXIT_FAILURE);
  }

  ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();

  SystemEvolution& evol = factory.createSimulation(filename, timestep);

  evol.setNSteps(nsteps);
  evol.setDumpFreq(freq);
  evol.setTemperatureField();
  evol.setHeatSource(source);
  evol.copyTemperatureField();
  evol.setTimeStep();
  
  evol.evolve();

  System& system = evol.getSystem();

  Matrix<complex>* temperature_field = system.getTemperatureField();
  Matrix<complex>* original_field = evol.getOriginalField();

  // Print the final temperature
  std::cout << "Final temperature field:" << std::endl;
  for (unsigned int i = 0; i < temperature_field->size(); i++) {
    for (unsigned int j = 0; j < temperature_field->size(); j++) {
      std::cout << (*temperature_field)(i, j) << " ";
    }
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
