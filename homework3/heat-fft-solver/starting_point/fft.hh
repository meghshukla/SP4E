#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

struct FFT {
  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);
  static Matrix<std::complex<int>> computeFrequencies(UInt size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
    UInt size = m_in.rows(); // Assuming square matrices
    Matrix<complex> m_out(size);

    fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data());
    fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
    fftw_plan plan = fftw_plan_dft_2d(size, size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
    UInt size = m_in.rows(); // Assuming square matrices
    Matrix<complex> m_out(size);

    fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data());
    fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
    fftw_plan plan = fftw_plan_dft_2d(size, size, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    for (UInt i = 0; i < size * size; ++i) {
        m_out.data()[i] /= (size * size);  // Normalize
    }

    return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(UInt size) {
    Matrix<std::complex<int>> frequencies(size);

    for (UInt i = 0; i < size; ++i) {
        for (UInt j = 0; j < size; ++j) {
            int fx = (i <= size / 2) ? i : i - size;
            int fy = (j <= size / 2) ? j : j - size;
            frequencies(i, j) = std::complex<int>(fx, fy);
        }
    }

    return frequencies;
}

#endif  // FFT_HH

