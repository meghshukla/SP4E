#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>
#include "my_types.hh"

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {
    Matrix<complex>* heat_source = system.getHeatSource();
    Matrix<complex>* temperature_field = system.getTemperatureField();

    Matrix<complex> derivative(temperature_field->size());
    Matrix<complex> frequencies = FFT::computeFrequencies(temperature_field->size());

    Matrix<complex> temp_F = FFT::transform(*temperature_field);
    Matrix<complex> heat_F = FFT::transform(*heat_source);

    double timestep = system.timestep;

    for (unsigned int i = 0; i < temperature_field->size(); i++) {
        for (unsigned int j = 0; j < temperature_field->size(); j++) {
            double q_x2 = frequencies(i, j).real();
            q_x2 = 2 * M_PI * q_x2 / temperature_field->size();
            q_x2 = pow(q_x2, 2);

            double q_y2 = frequencies(i, j).imag();
            q_y2 = 2 * M_PI * q_y2 / temperature_field->size();
            q_y2 = pow(q_y2, 2);
            
            derivative(i, j) = (heat_F)(i, j) - ((temp_F)(i, j) * (q_x2 + q_y2));

        }
    }
    derivative = FFT::itransform(derivative);

    for (unsigned int i = 0; i < temperature_field->size(); i++) {
        for (unsigned int j = 0; j < temperature_field->size(); j++) {
            (*temperature_field)(i, j) += (timestep * derivative(i, j));
        }
    }
    /*
    for (auto&& entry : index(frequencies)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);
        std::cout << i << "," << j << " = " << val << std::endl;
    }
    */
}

/* -------------------------------------------------------------------------- */
