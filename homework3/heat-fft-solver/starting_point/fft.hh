#ifndef FFT_HH
#define FFT_HH
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
#include <cmath>
#include <cstring>

/* ------------------------------------------------------ */

struct FFT {
  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);
  static Matrix<complex> computeFrequencies(int size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) { //This code defines the transform function for the FFT struct. The function performs a forward 2D discrete Fourier Transform (DFT) on the input Matrix<complex> using the FFTW library.
    UInt rows = m_in.rows(); // Determining matrix dimensions.
    UInt cols = m_in.cols();
    Matrix<complex> m_out(rows); //Constructs an empty output matrix m_out with the same dimensions (rows) as the input matrix. This matrix will store the result of the FFT computation.


    // Pointer Conversion.
    fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data()); // This cast is converting the data() pointer from std::complex<double>* (used in the Matrix class) into fftw_complex* (used by the FFTW library).
    fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
    
    // Plan Creation
    fftw_plan plan = fftw_plan_dft_2d(rows, cols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    return m_out;
}


/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
    UInt rows = m_in.rows();
    UInt cols = m_in.cols();
    Matrix<complex> m_out(rows);

    fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data()); // This cast is converting the data() pointer from std::complex<double>* (used in the Matrix class) into fftw_complex* (used by the FFTW library).
    fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
    fftw_plan plan = fftw_plan_dft_2d(rows, cols, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    // Normalize the result (divide by N^2 after inverse FFT)
    for (auto&& entry : m_out.storage) {
        entry /= static_cast<double>(rows * cols);
    }

    return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::computeFrequencies(int size) {
    Matrix<complex> frequencies(size);

    // Generate wavenumbers: 0, 1, ..., size/2, -size/2+1, ..., -1
    for (int i = 0; i < size; ++i) {
        double freq_x = (i <= size / 2) ? i : (i - size);
        for (int j = 0; j < size; ++j) {
            double freq_y = (j <= size / 2) ? j : (j - size);
            frequencies(i, j) = complex(freq_x, freq_y);  // (kx, ky)
        }
    }

    return frequencies;
}

/* ------------------------------------------------------ */


#endif  // FFT_HH

