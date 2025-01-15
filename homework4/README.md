# SP4E: Homework 4

C++ and Python: Eigen and PyBind

## Table of Contents

- [Exercise 1](#Exercise 1)
- [Exercise 2: Eigen](#Exercise 2: Eigen)
- [Exercise 3, 4, 5: PyBind11](#Exercise 3, 4, 5: PyBind11)


## Installation

```
# Clone the repository
git clone https://github.com/meghshukla/SP4E.git

# Navigate to the project directory
cd SP4E/homework4/starting_point
```

This code requires googletest installed, a popular C++ testing framework. We recommend following the instructions in https://www.jetbrains.com/help/objc/creating-google-test-run-debug-configuration-for-test.html 

While the CMAKELists.txt file can be used to build the executable, it is highly recommended to keep the default settings in it. For instance, FFTW is highly recommended. Instructions included creating a ```build``` directory, running ``` cmake ../ ; make ```

## Exercise 1

We followed the same process as last time to study the code using Doxyfile

## Exercise 2: Eigen

Evaluation command: ```GTest: cmake ../; make; ./test_finite_diff```

We completed the two methods in the file ```compute_temperature_finite_differences.cc```.
Once we had the LHS and RHS we could use the solver to get our solution. We ran the TEST cases, passing both the tests.


pip install pybind11 conda uninstall gcc
## Exercise 3, 4, 5: PyBind11

We installed PyBind using ```pip install pybind11```, which was straightforward. However, using PyBind11 was tricky since there were multiple versions of ```gcc``` installed which was hard to catch. We therefore recommend using only one version. Common sources of multiple installation include system-wide GCC installation and conda installation of GCC.

Another challenge came from the complexity of the code. As a result we took considerable time to implement the bindings, particulary noting that not only the Derived class but also the Base class needs binding. While this was trivial for ```Compute*``` and ```Factory*``` classes, we faced issues with ```CsvWriter```. This is because while the exercise for the first two requires binding the base classes, ```CsvWriter``` had no such requirement. Once we bound the ```Compute``` class in ```CsvWriter```, we could proceed without any issues.

Additionally, we used ```setuptools``` in Python to bind C++ to Python code. We found this method easier to debug. As a result, we made three files per exercise. 
1. ```compute_bindings.hh / factory_bindings.hh / csv_bindings.hh```: These files contained all the headers needed to run the binding.

2. ```compute_bindings.cc / factory_bindings.cc / csv_bindings.cc```: These files contained the actual binding logic for all the classes needed.

3. ```setup_compute.py / setup_factory.py / setup_csv.py```: These files used the Python interface of PyBind to do the binding. This required specifying various source files, libraries and module name. Example script to run: ```python setup_compute.py build_ext --inplace```

4. ```PyCompute.cpython-39-x86_64-linux-gnu.so AND PyCSV.cpython-39-x86_64-linux-gnu.so AND PyFactory.cpython-39-x86_64-linux-gnu.so```: These files are Python modules containing the C++ objects. We import this in ```main.py``` using ```import PyCompute, PyCSV, PyFactory```.

### Exercise 3.2

```CreateSimulation``` creates a SystemEvolve object which is used to run the simulation. This implementation depends on the particle chosen: material point, planet or ping pong ball. Since the design followed is Singleton, there exists a virtual function with the same name which has to be overridden. We argue that it has to be overriden since the constructor of ParticlesFactoryInterface is private, and therefore no object can be created from it outside of the class. The Singleton design ensures that only one object is created which is derived from ParticlesFactoryInterface. This derived class has to override the virtual CreateSimulation in the absence of which the function is not reachable. The functor uses templates which allows for different functions to be applied to the particles. 

### Exercise 3.3

```CreateSimulation``` does not necessarily require overload since the virtual function with two arguments is not used in practice. In practice, an object of the derived class calls CreateSimulation using the functor formulation which sets up the simulation. To make our code simpler, we do not bind the two argument virtual function. We bind the functor using ```py::function`` where py is the namespace for pybind11.


### Exercise 4.2 

This requires using ```py::return_value_policy::reference``` or value. Managing references is important since C++ and Python handle memory allocation differently. By using ```reference```, we can make Python accept (deny if value is used) ownership of the memory corresponding to the object.

### Exercise 5

The only binding required was for ```CsvWriter```. 

