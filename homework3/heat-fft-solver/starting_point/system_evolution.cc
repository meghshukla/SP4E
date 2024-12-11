#include "system_evolution.hh"
#include "csv_writer.hh"
/* -------------------------------------------------------------------------- */
#include <iomanip>
#include <sstream>
/* -------------------------------------------------------------------------- */

SystemEvolution::SystemEvolution(std::unique_ptr<System> system)
    : system(std::move(system)) {}

/* -------------------------------------------------------------------------- */

void SystemEvolution::evolve() {
  for (UInt i = 0; i < nsteps; ++i) {

    for (auto& compute : computes)
      /*There's only one compute: Temperature for now*/
      compute->compute(*system);

    if (i % freq == 0) {
      std::stringstream sstr;
      sstr << "dumps/step-" << std::setfill('0') << std::setw(5) << i << ".csv";
      CsvWriter dumper(sstr.str());
      dumper.write(*system);

      // Print values of temperature_field
      for (unsigned int i = 0; i < temperature_field->size(); i++) {
          for (unsigned int j = 0; j < temperature_field->size(); j++) {
              std::cout << (*temperature_field)(i, j) << " ";
          }
          std::cout << std::endl;
      }
      std::cout << std::endl << std::endl << std::endl;


    }
  }
}

/* -------------------------------------------------------------------------- */

void SystemEvolution::addCompute(const std::shared_ptr<Compute>& compute) {
  computes.push_back(compute);
}

/* -------------------------------------------------------------------------- */
void SystemEvolution::setNSteps(UInt nsteps) { this->nsteps = nsteps; }
/* -------------------------------------------------------------------------- */
void SystemEvolution::setDumpFreq(UInt freq) { this->freq = freq; }
/* -------------------------------------------------------------------------- */
void SystemEvolution::setHeatSource(std::string source) {
  this->heat_source = new Matrix<complex>(this->size_field);

  for (unsigned int i = 0; i < this->size_field; i++) {
    for (unsigned int j = 0; j < this->size_field; j++) {
      // If source == "none" then set all values to 0 else set to sine
      if (source == "none")
        (*heat_source)(i, j) = 0;
      else {
        double x = 2 * (j / (static_cast< float >(this->size_field) - 1)) - 1;
        (*heat_source)(i, j) = complex(sin(M_PI * x) * M_PI * M_PI, 0.);
      }
    }
  }
  system->setHeatSource(heat_source);
  /* Debugging code*/
  /*
  for (unsigned int i = 0; i < this->size_field; i++) {
    for (unsigned int j = 0; j < this->size_field; j++) {
      std::cout << (*heat_source)(i, j) << " ";
    }
    std::cout << std::endl;
  }
  */
}

/* -------------------------------------------------------------------------- */
void SystemEvolution::setTemperatureField() {
  this->size_field = 20;
  this->temperature_field = new Matrix<complex>(this->size_field);

  for (unsigned int i = 0; i < this->size_field; i++) {
    for (unsigned int j = 0; j < this->size_field; j++) {
      //(*temperature_field)(i, j) = complex(static_cast<double>(rand()) / static_cast<double>(RAND_MAX), 0.);
      (*temperature_field)(i, j) = complex(3., 0.);
    }
  }
  system->setTemperatureField(temperature_field);
  /* Debugging code*/
  /*
  for (unsigned int i = 0; i < this->size_field; i++) {
    for (unsigned int j = 0; j < this->size_field; j++) {
      std::cout << (*temperature_field)(i, j);
    }
    std::cout << std::endl;
  }
  for (auto&& entry : index(*temperature_field)) {
    std::cout << std::get<2>(entry) << std::endl;
  }
  */
}

void SystemEvolution::copyTemperatureField() {
  this->original_field = new Matrix<complex>(this->size_field);

  for (unsigned int i = 0; i < this->size_field; i++) {
    for (unsigned int j = 0; j < this->size_field; j++) {
      (*original_field)(i, j) = (*temperature_field)(i, j);
    }
  }
}

void SystemEvolution::setTimeStep() {
  system->timestep = timestep;
}

Matrix<complex>* SystemEvolution::getOriginalField() {
  return original_field;
}
/* -------------------------------------------------------------------------- */
System& SystemEvolution::getSystem() { return *system; }
/* -------------------------------------------------------------------------- */
