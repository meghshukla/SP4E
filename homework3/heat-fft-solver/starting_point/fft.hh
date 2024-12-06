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
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
    UInt rows = m_in.rows();
    UInt cols = m_in.cols();
    Matrix<complex> m_out(rows);

    fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data());
    fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
    fftw_plan plan = fftw_plan_dft_2d(rows, cols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    // Remove manual normalization (let FFTW handle it)
    return m_out;
}


/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
    UInt rows = m_in.rows();
    UInt cols = m_in.cols();
    Matrix<complex> m_out(rows);

    fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data());
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


#endif  // FFT_HH

