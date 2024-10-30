#ifndef DUMPER_SERIES_HH
#define DUMPER_SERIES_HH

#include <iostream>
#include <iomanip> // For setting precision
#include "series.hh"

// Series printing
class DumperSeries {
public:
    DumperSeries(Series& series) : series(series), precision(6) {}  // Constructor to initialize reference and default precision
    virtual void dump(std::ostream& os) = 0;
    virtual void setPrecision(unsigned int precision) {
        this->precision = precision;
    }
protected:
    Series& series;
    unsigned int precision;
};

inline std::ostream& operator<<(std::ostream& stream, DumperSeries& _this) {
    _this.dump(stream);
    return stream;
}

class PrintSeries : public DumperSeries {
public:
    PrintSeries(Series& series, int frequency)
        : DumperSeries(series), frequency(frequency) {}

    void dump(std::ostream& os) override {
        os << std::fixed << std::setprecision(precision);
        for (unsigned int i = 0; i < series.length; i += frequency) {
            os << "Value at index " << i << ": " << series.storedArray[i] << std::endl;
        }
    }

private:
    int frequency;
};

class WriteSeries : public DumperSeries {
public:
    WriteSeries(Series& series, int maxIter) 
        : DumperSeries(series), maxIter(maxIter), separator(' ') {} // Default separator is space

    void setSeparator(char sep) {
        separator = sep;
    }

    void dump(std::ostream& os) override {
        std::string filename;
        switch (separator) {
            case ',':
                filename = "output.csv";
                break;
            case '|':
                filename = "output.psv";
                break;
            case ' ':
            case '\t':
            default:
                filename = "output.txt";
                break;
        }

        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        outFile << std::fixed << std::setprecision(precision);
        for (int i = 1; i <= maxIter; i++) {
            outFile << i << separator << series.storedArray[i-1] << std::endl;
        }
        outFile << "Checking for analytic solution." << std::endl;
        
        // Using x?y:z operator to check if the analytic solution is NaN
        std::isnan(series.getAnalyticPrediction()) ? outFile << "No analytic solution." << std::endl
        : outFile << "Analytic solution: " << series.getAnalyticPrediction() << std::endl;

        outFile.close();
    }

private:
    int maxIter;
    char separator;
};

#endif