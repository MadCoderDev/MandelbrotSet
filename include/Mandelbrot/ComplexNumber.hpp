#pragma once

// headers
#include <x86intrin.h>

// types
typedef union
{
    __m128d xmm;
    struct {double re; double im; };
} _rawComplex;

// classes
class ComplexNumber
{
private:
    // members
    _rawComplex number;

public:
    // constructors
    ComplexNumber(double re, double im);
    ComplexNumber();

    // destructors
    ~ComplexNumber();

    // methods
    ComplexNumber& Sqr();
    double SqrMag();
    ComplexNumber& Add(const ComplexNumber &c);
    ComplexNumber& Multiply(const ComplexNumber &c);

    // getters
    inline double Re() const { return number.re; }
    inline double Im() const { return number.im; }

    // setters
    inline void Re(double val) { this->number.xmm = _mm_setr_pd(val, this->number.im); }
    inline void Im(double val) { this->number.xmm = _mm_setr_pd(this->number.re, val); }

};
