from setuptools import setup, Extension
import pybind11

# Define the extension module
compute_module = Extension(
    'PyCompute',                            # Module name in Python
    sources=['compute_bindings.cpp', 'system.cc', 'system_evolution.cc', 'planets_factory.cc',
             'planet.cc', 'ping_pong_balls_factory.cc', 'ping_pong_ball.cc','particles_factory_interface.cc',
             'particle.cc', 'material_points_factory.cc', 'material_point.cc', 'csv_writer.cc', 'csv_reader.cc',
             'compute_boundary.cc', 'compute_contact.cc', 'compute_energy.cc', 'compute_gravity.cc',
             'compute_interaction.cc', 'compute_kinetic_energy.cc', 'compute_potential_energy.cc',
             'compute_temperature_finite_differences.cc', 'compute_temperature.cc', 
             'compute_verlet_integration.cc'],              # Source files
    
    include_dirs=[pybind11.get_include(),
                  './eigen',
                  './',
                  '/usr/local/include'], # Include pybind11 headers
    library_dirs=['/usr/local/lib'],       # Library directory for FFTW (adjust path if necessary)
    libraries=['fftw3'],                   # Link against the FFTW library
    language='c++',                        # Specify C++ language
    extra_compile_args=['-std=c++14'],     # Specify C++14 standard
    extra_link_args=['-std=c++14'],        # Specify C++14 standard
)

# Build the module
setup(
    name='PyCompute',
    version='0.1',
    ext_modules=[compute_module],
)