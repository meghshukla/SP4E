#ifndef __SYSTEM_EVOLUTION__HH__
#define __SYSTEM_EVOLUTION__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "system.hh"
#include "matrix.hh"
/* -------------------------------------------------------------------------- */

//! Manager for system evolution
class SystemEvolution {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  //! Construct using existing system (takes ownership)
  SystemEvolution(std::unique_ptr<System> system);

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  //! Evolve all time steps
  void evolve();
  //! Add compute to list of computes
  void addCompute(const std::shared_ptr<Compute>& compute);
  //! Get the system object
  System& getSystem();

  void setNSteps(UInt nsteps);
  void setDumpFreq(UInt freq);
  void setHeatSource(std::string source);
  void setTemperatureField();
  void copyTemperatureField();
  Matrix<complex>* getOriginalField();

  /* ------------------------------------------------------------------------ */
  /* Members                                                                  */
  /* ------------------------------------------------------------------------ */
protected:
  std::vector<std::shared_ptr<Compute>> computes;
  std::unique_ptr<System> system;
  UInt nsteps, freq;
  Matrix<complex>* heat_source;
  Matrix<complex>* temperature_field;
  Matrix<complex>* original_field;
  int size_field;
};

/* -------------------------------------------------------------------------- */
#endif  //__SYSTEM_EVOLUTION__HH__
