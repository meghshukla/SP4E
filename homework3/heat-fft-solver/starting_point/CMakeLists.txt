cmake_minimum_required(VERSION 3.1)
project(Particles)

set(CMAKE_CXX_STANDARD 14)

################################################################
# Options
################################################################
# Option to enable or disable FFTW functionality
option(ENABLE_FFT "Enable FFTW functionality" ON)

################################################################
# Find FFTW
################################################################
if(ENABLE_FFT)
  find_path(FFTW3_INCLUDE_DIR fftw3.h PATHS /usr/include /usr/local/include)
  find_library(FFTW3_LIBRARY NAMES fftw3 PATHS /usr/lib /usr/local/lib)
  
  if(FFTW3_INCLUDE_DIR AND FFTW3_LIBRARY)
    message(STATUS "FFTW3 found")
    set(FFTW3_LIBRARIES ${FFTW3_LIBRARY})
    set(FFTW3_INCLUDE_DIRS ${FFTW3_INCLUDE_DIR})
  else()
    message(FATAL_ERROR "FFTW3 not found! Install it using `sudo apt install libfftw3-dev`.")
  endif()
endif()

################################################################
# libpart
################################################################
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

# Add FFTW dependencies to the library if enabled
if(ENABLE_FFT)
  target_include_directories(part PUBLIC ${FFTW3_INCLUDE_DIRS})
  target_link_libraries(part PUBLIC ${FFTW3_LIBRARIES})
endif()

################################################################
# Executables
################################################################
add_executable(particles main.cc)
target_link_libraries(particles gtest_main gtest pthread part)

if(EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
  add_subdirectory(googletest)

  add_executable(test_kepler test_kepler.cc)
  add_executable(test_fft test_fft.cc)

  target_link_libraries(test_kepler part gtest_main gtest pthread)

  if(ENABLE_FFT)
    target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW3_LIBRARIES})
  else()
    target_link_libraries(test_fft part gtest_main gtest pthread)
  endif()

  add_custom_target(test ./test_kepler && ./test_fft DEPENDS part test_kepler test_fft)
else()
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
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
  set(DOXYGEN_EXCLUDE_PATTERNS */googletest/*)

  doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
  )
  add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)

