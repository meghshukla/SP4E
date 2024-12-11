#include "system.hh"

Particle& System::getParticle(UInt i) { return *list_particles[i]; }

/* -------------------------------------------------------------------------- */

void System::addParticle(const std::shared_ptr<Particle>& new_particle) {
  list_particles.push_back(new_particle);
}

/* -------------------------------------------------------------------------- */

UInt System::getNbParticles() { return list_particles.size(); }

// Getter for temperature_field
Matrix<complex>* System::getTemperatureField() const {
    return temperature_field;
}

// Setter for temperature_field
void System::setTemperatureField(Matrix<complex>* temperature_field) {
    this->temperature_field = temperature_field;
}

// Getter for heat_source
Matrix<complex>* System::getHeatSource() const {
    return heat_source;
}

// Setter for heat_source
void System::setHeatSource(Matrix<complex>* heat_source) {
    this->heat_source = heat_source;
}