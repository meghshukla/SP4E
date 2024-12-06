#include "fft.hh"
#include "my_types.hh"
#include <gtest/gtest.h>

/*****************************************************************/
// Test for the forward FFT transform
/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    // Update this line to use the corrected scaling expectation
    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), (N * N) / 2, 1e-6);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), (N * N) / 2, 1e-6);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-6);
  }
}
/*****************************************************************/


/*****************************************************************/
// Test for the inverse FFT transform
TEST(FFT, inverse_transform) {
  UInt N = 128;  // Smaller size for quick validation
  Matrix<complex> m(N);  // Create a square matrix of size N

  // Fill the matrix with a simple cosine function
  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);  // Assign cosine values
  }

  // Perform forward and inverse FFT
  Matrix<complex> transformed = FFT::transform(m);
  Matrix<complex> result = FFT::itransform(transformed);

  // Validate that the original matrix is reconstructed
  for (auto&& entry : index(result)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    // Ensure the reconstructed values match the original
    ASSERT_NEAR(std::real(val), std::real(m(i, j)), 1e-10);
    ASSERT_NEAR(std::imag(val), std::imag(m(i, j)), 1e-10);  // Imaginary part
  }
}

/*****************************************************************/
