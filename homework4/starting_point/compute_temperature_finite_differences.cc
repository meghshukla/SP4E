#include "compute_temperature_finite_differences.hh"
#include "material_point.hh"
#include "matrix.hh"

void ComputeTemperatureFiniteDifferences::compute(System& system) {

  if (should_factorize) {
    assembleLinearOperator(system);
    A.makeCompressed();
    solver->analyzePattern(A);
    solver->factorize(A);

    should_factorize = false;
  }

  auto N = system.getNbParticles();

  Eigen::VectorXd theta(N);

  assembleRightHandSide(system);
  theta = solver->solve(rhs);

  // Transferring temperature back
  auto it = theta.begin();
  for (auto& part : system) {
    static_cast<MaterialPoint&>(part).getTemperature() = (*it);
    ++it;
  }
}

void ComputeTemperatureFiniteDifferences::assembleLinearOperator(
    System& system) {
    
    auto N = system.getNbParticles();

    // Number of grid points
    UInt numPoints = N * N;

    A.resize(numPoints, numPoints);
    
    // Grid spacing (assuming uniform)
    double h = 1. / N;

    // Precompute material factor
    double materialFactor = 0.1 / (h * h);

    // Fill the matrix
    std::vector<Eigen::Triplet<double>> triplets; // Triplet format for sparse insertion

    for (UInt i = 0; i < N; ++i) {
        for (UInt j = 0; j < N; ++j) {
            UInt index = i * N + j; // Flatten 2D index to 1D

            // Diagonal (self)
            triplets.emplace_back(index, index, 1.0 + 4.0 * materialFactor);

            // Left neighbor
            if (i > 0) {
                UInt leftIndex = (i - 1) * N + j;
                triplets.emplace_back(index, leftIndex, -materialFactor);
            }

            // Right neighbor
            if (i < N - 1) {
                UInt rightIndex = (i + 1) * N + j;
                triplets.emplace_back(index, rightIndex, -materialFactor);
            }

            // Top neighbor
            if (j > 0) {
                UInt topIndex = i * N + (j - 1);
                triplets.emplace_back(index, topIndex, -materialFactor);
            }

            // Bottom neighbor
            if (j < N - 1) {
                UInt bottomIndex = i * N + (j + 1);
                triplets.emplace_back(index, bottomIndex, -materialFactor);
            }
        }
    }

    // Set values in the sparse matrix
    A.setFromTriplets(triplets.begin(), triplets.end());

}

void ComputeTemperatureFiniteDifferences::assembleRightHandSide(
    System& system) {
      // Number of particles in the system
    UInt numParticles = system.getNbParticles();

    // Initialize the RHS vector
    rhs.resize(numParticles);

    // Material property constant: Δt / (ρC)
    //double materialFactor = delta_t / (density * capacity);
    double materialFactor = 1.0;

    // Assemble the RHS
    for (UInt i = 0; i < numParticles; ++i) {
        // Access the particle as a MaterialPoint
        auto& particle = static_cast<MaterialPoint&>(system.getParticle(i));

        // Get the particle's heat source and current temperature
        double heatSource = particle.getHeatSource();
        double temperature = particle.getTemperature();

        // Compute RHS for the particle
        rhs[i] = materialFactor * heatSource + temperature;
    }
}
