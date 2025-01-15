Ex. 2: 
For GTest: cmake ../; make; ./test_finite_diff

Ex. 4: 
compute_interaction.hh, compute_bindings.cpp, compute_bindings.hh, setup_compute.py
python setup_compute.py build_ext --inplace
Generated file: compute.cpython-39-x86_64-linux-gnu.so

Ex. 3:
factory_bindings.hh, factory_bindings.cpp, setup_factory.py
python setup_factory.py build_ext --inplace
Generated file: factory.cpython-39-x86_64-linux-gnu.so

Ex. 5:
csv_bindings.hh, csv_bindings.cpp, setup_csv.py
python setup_csv.py build_ext --inplace
Generated file: csv_writer.cpython-39-x86_64-linux-gnu.so