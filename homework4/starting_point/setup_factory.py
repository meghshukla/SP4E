from setuptools import setup, Extension
import pybind11

# Define the extension module
factory_module = Extension(
    'factory',                            # Module name in Python
    sources=['factory_bindings.cpp'],              # Source files
    include_dirs=[pybind11.get_include(),
                  './eigen',
                  './'], # Include pybind11 headers
    language='c++',                        # Specify C++ language
    extra_compile_args=['-std=c++14'],     # Specify C++14 standard
    extra_link_args=['-std=c++14'],        # Specify C++14 standard
)

# Build the module
setup(
    name='factory',
    version='0.1',
    ext_modules=[factory_module],
)