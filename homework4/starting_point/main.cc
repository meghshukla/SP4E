#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_points_factory.hh"
#include "my_types.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"
#include "system.hh"
#include "compute_temperature.hh" // Included for testing RHS assembly
/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <iostream>
#include <sstream>
/* -------------------------------------------------------------------------- */

int main(int argc, char** argv) {
  if (argc < 6) {
    std::cout << "Usage: " << argv[0]
              << " nsteps dump_freq input.csv particle_type timestep [test_rhs]"
              << std::endl;
    std::cout << "\tparticle type can be: planet, ping_pong, material_point"
              << std::endl;
    std::cout << "\tOptional: Provide 'test_rhs' as the 6th argument to test RHS assembly"
              << std::endl;
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

  // Optional: Test RHS assembly if "test_rhs" is provided as the 6th argument
  if (argc == 7 && std::string(argv[6]) == "test_rhs") {
    // Create a mock system for testing
    System system;

    // Add mock particles to test the RHS for these given values.
    for (int i = 0; i < 4; ++i) {
      auto particle = std::make_shared<MaterialPoint>();
      particle->getTemperature() = 300.0 + i * 10; // Example temperatures
      particle->getHeatSource() = 10.0 * (i + 1);  // Example heat sources
      system.addParticle(particle);
    }

    // Create ComputeTemperature instance
    ComputeTemperature computeTemp;
    computeTemp.getDeltat() = 0.1;       // Time step
    computeTemp.getConductivity() = 1.0; // Conductivity
    computeTemp.getDensity() = 1.0;      // Density
    computeTemp.getCapacity() = 1.0;     // Heat capacity

    // Assemble RHS
    Eigen::VectorXd rhs = computeTemp.assembleRHS(system);

    // Output RHS for validation
    std::cout << "Assembled RHS:\n" << rhs << std::endl;

    return EXIT_SUCCESS; // End program after RHS testing
  }


  // Test Matrix Assembly
  if (argc == 7 && std::string(argv[6]) == "test_matrix") {
    UInt N = 2; // Example grid size
    ComputeTemperature computeTemp;
    computeTemp.getDeltat() = 0.1;
    computeTemp.getConductivity() = 1.0;
    computeTemp.getDensity() = 1.0;
    computeTemp.getCapacity() = 1.0;
    computeTemp.getL() = 1.0;

    Eigen::SparseMatrix<double> A = computeTemp.assembleMatrix(N);


    // Output Matrix for validation
    std::cout << "Assembled Matrix A:\n" << Eigen::MatrixXd(A) << std::endl;

    return EXIT_SUCCESS;
  }
  

  // Testing the Linear System Solver 

  if (argc == 7 && std::string(argv[6]) == "test_solve") {
    UInt N = 2; // Grid size

    // Create a ComputeTemperature instance
    ComputeTemperature computeTemp;
    computeTemp.getDeltat() = 0.1;
    computeTemp.getConductivity() = 1.0;
    computeTemp.getDensity() = 1.0;
    computeTemp.getCapacity() = 1.0;
    computeTemp.getL() = 1.0;

    // Assemble the matrix A
    Eigen::SparseMatrix<double> A = computeTemp.assembleMatrix(N);

    // Create a mock RHS vector b
    Eigen::VectorXd b(N * N);
    b << 1.0, 2.0, 3.0, 4.0; // Example values

    // Solve the system A * x = b
    Eigen::VectorXd x = computeTemp.solveSystem(A, b);

    // Print the solution
    std::cout << "Solution x:\n" << x << std::endl;

    return EXIT_SUCCESS;
}




  // Original functionality: Initialize the simulation
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

  CsvWriter dumper("init.csv");
  dumper.write(evol.getSystem());

  evol.setNSteps(nsteps);
  evol.setDumpFreq(freq);

  evol.evolve();

  return EXIT_SUCCESS;
}
