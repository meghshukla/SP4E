#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include <Eigen/Dense>
#include <Eigen/SparseCore>

//! Compute heat equation evolution
class ComputeTemperature : public Compute {
public:
  //! Temperature evolution implementation
  void compute(System& system) override;

  // Assemble the RHS of the heat equation
  Eigen::VectorXd assembleRHS(System& system); // Removed const to match implementation

  // Assemble the Matrix of the heat equation
  Eigen::SparseMatrix<double> assembleMatrix(UInt N);

  // Solve the sparse system of equations.
  Eigen::VectorXd solveSystem(const Eigen::SparseMatrix<double>& A, const Eigen::VectorXd& b);


  //! Return the heat conductivity
  Real& getConductivity() { return conductivity; };
  //! Return the heat capacity
  Real& getCapacity() { return capacity; };
  //! Return the density
  Real& getDensity() { return density; };
  //! Return the characteristic length of the square
  Real& getL() { return L; };
  //! Return the time step
  Real& getDeltat() { return delta_t; };

  bool implicit = true;

private:
  Real conductivity;
  Real capacity;
  Real density;
  //! Side length of the problem
  Real L;

  Real delta_t;
};

/* -------------------------------------------------------------------------- */
#endif  // __COMPUTE_TEMPERATURE__HH__
