#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <stdexcept>
#include <iostream>
#include <cmath>

/* -------------------------------------------------------------------------- */

// Assemble the RHS of the heat equation
Eigen::VectorXd ComputeTemperature::assembleRHS(System& system) {
    // Number of particles in the system
    UInt numParticles = system.getNbParticles();

    // Initialize the RHS vector
    Eigen::VectorXd rhs(numParticles);

    // Material property constant: Δt / (ρC)
    double materialFactor = delta_t / (density * capacity);

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

    return rhs;
}


// Assemble the system matrix for the heat equation
Eigen::SparseMatrix<double> ComputeTemperature::assembleMatrix(UInt N) {
    // Number of grid points
    UInt numPoints = N * N;

    // Create a sparse matrix of size N^2 x N^2
    Eigen::SparseMatrix<double> A(numPoints, numPoints);

    // Grid spacing (assuming uniform)
    double h = L / N;

    // Precompute material factor
    double materialFactor = delta_t * conductivity / (density * capacity * h * h);

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

    return A;
}

// Compute the temperature evolution
void ComputeTemperature::compute(System& system) {
    if (!implicit) {
        // Original FFT-based explicit integration logic (unchanged)
        UInt size = system.getNbParticles();
        UInt N = std::sqrt(size);
        Matrix<complex> temperature(N);
        Matrix<complex> heat_source(N);

        std::transform(system.begin(), system.end(), temperature.begin(),
                       [](auto& part) {
                           return static_cast<MaterialPoint&>(part).getTemperature();
                       });

        std::transform(system.begin(), system.end(), heat_source.begin(),
                       [](auto& part) {
                           return static_cast<MaterialPoint&>(part).getHeatSource();
                       });

        auto freqs = FFT::computeFrequencies(N);
        auto h_hat = FFT::transform(heat_source);
        auto T_hat = FFT::transform(temperature);
        auto T_rate_hat = Matrix<complex>(N);

        const auto factor = delta_t * density / capacity;
        const auto factor2 = 1. / density / capacity;

        auto explicit_integrator = [&](auto&& entry) {
            int i = std::get<0>(entry);
            int j = std::get<1>(entry);
            auto& T_rate = std::get<2>(entry);
            auto f = freqs(i, j);
            Real k2 = std::abs(complex(f.real(), f.imag())) * 2. * M_PI / L;
            k2 *= k2;

            T_rate_hat(i, j) =
                1. / factor2 * (h_hat(i, j) + T_hat(i, j) * conductivity * k2);
        };

        for (auto entry : index(T_rate_hat))
            explicit_integrator(entry);

        auto temperature_rate = FFT::itransform(T_rate_hat);
        auto it_temp_rate = temperature_rate.begin();
        for (auto& part : system) {
            auto& p = static_cast<MaterialPoint&>(part);

            p.getTemperatureRate() = (*it_temp_rate).real();
            p.getTemperature() += delta_t * p.getTemperatureRate();
            ++it_temp_rate;
        }

    } else {
        // Call the new RHS assembly (minimal addition)
        Eigen::VectorXd rhs = assembleRHS(system);
        std::cout << "Assembled RHS:\n" << rhs << std::endl;

        // Integrators for implicit solving can be implemented here if needed
    }
}

/* -------------------------------------------------------------------------- */
