from setuptools import setup, Extension
import pybind11

# Define the extension module
csv_writer_bindings_module = Extension(
    'csv_writer',                 # Module name in Python
    sources=['csv_bindings.cpp'],  # Source files
    include_dirs=[pybind11.get_include(),
                  './eigen',
                  './'], # Include pybind11 headers
    language='c++',                        # Specify C++ language
    extra_compile_args=['-std=c++14'],     # Specify C++14 standard
    extra_link_args=['-std=c++14'],        # Specify C++14 standard
)

# Build the module
setup(
    name='csv_writer',
    version='0.1',
    ext_modules=[csv_writer_bindings_module],
)