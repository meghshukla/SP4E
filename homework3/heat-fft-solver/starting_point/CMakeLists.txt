cmake_minimum_required (VERSION 3.1)
project (Particles)

# Set the C++ standard to 14
set(CMAKE_CXX_STANDARD 14)

################################################################
# FFTW Option
################################################################

# Option to enable or disable FFTW support.
# Use -DUSE_FFTW=ON or -DUSE_FFTW=OFF when running cmake to enable/disable this feature.
option(USE_FFTW "Enable FFTW support" ON)

# Locate the FFTW library manually
if(USE_FFTW)
  find_library(FFTW_LIBRARIES fftw3 REQUIRED)
  find_path(FFTW_INCLUDES fftw3.h REQUIRED)

  if(FFTW_LIBRARIES AND FFTW_INCLUDES)
    message(STATUS "FFTW library found: ${FFTW_LIBRARIES}")
    message(STATUS "FFTW includes found: ${FFTW_INCLUDES}")
    include_directories(${FFTW_INCLUDES})
  else()
    message(FATAL_ERROR "FFTW library or includes not found. Ensure FFTW is installed.")
  endif()
endif()

################################################################
# libpart
################################################################

# Create a library named 'part' from the provided source files
add_library(part
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  compute_temperature.cc
  material_points_factory.cc 
  )

# Add an executable named 'particles' using main.cc
add_executable(particles main.cc)

# Link the 'particles' executable with the required libraries
target_link_libraries(particles gtest_main gtest pthread part)

################################################################
# Tests Setup
################################################################

if(EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
  # Add the googletest subdirectory
  add_subdirectory(googletest)

  # Create test executables for test_kepler and test_fft
  add_executable(test_kepler test_kepler.cc)
  add_executable(test_fft test_fft.cc)

  # Link FFTW to test_fft only if FFTW support is enabled
if(USE_FFTW)
  # Find the FFTW library
  find_library(FFTW_LIBRARIES fftw3 REQUIRED)
  find_path(FFTW_INCLUDES fftw3.h REQUIRED)

  # Ensure FFTW is found
  if(FFTW_LIBRARIES AND FFTW_INCLUDES)
    message(STATUS "FFTW library found: ${FFTW_LIBRARIES}")
    message(STATUS "FFTW includes found: ${FFTW_INCLUDES}")
    include_directories(${FFTW_INCLUDES})
  else()
    message(FATAL_ERROR "FFTW library or includes not found. Ensure FFTW is installed.")
  endif()

  # Add the test_fft target and link FFTW
  target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIBRARIES})
  target_compile_definitions(test_fft PUBLIC USE_FFTW)
else()
  # Add test_fft without FFTW if FFTW is disabled
  target_link_libraries(test_fft part gtest_main gtest pthread)
endif()
  
  
  
  

  # Link the 'test_kepler' executable with necessary libraries
  target_link_libraries(test_kepler part gtest_main gtest pthread)

  # Create a custom target to run all tests
  add_custom_target(test ./test_kepler && ./test_fft DEPENDS part test_kepler test_fft)
else()
  # If googletest is missing, notify the user with a message
  message("
*********************************************
google tests is missing. 
Did you forget `git submodule update --init`
*********************************************
")
  message(FATAL_ERROR "exit")
endif()

################################################################
# Doxygen
################################################################

# Setup Doxygen for generating documentation
find_package(Doxygen)
if (DOXYGEN_FOUND)

  # Exclude the googletest directory from the documentation
  set(DOXYGEN_EXCLUDE_PATTERNS */googletest/*)

  # Configure and add a target for Doxygen documentation
  doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
    )
  add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)

