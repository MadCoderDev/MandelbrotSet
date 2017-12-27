// headers
#include <Mandelbrot/ComplexNumber.hpp>

// constructors
ComplexNumber::ComplexNumber(double re, double im)
{
    this->number.xmm = _mm_setr_pd(re, im);
}

ComplexNumber::ComplexNumber()
{
    this->number.xmm = _mm_setr_pd(0, 0);
}

// destructors
ComplexNumber::~ComplexNumber()
{
}

// methods
ComplexNumber& ComplexNumber::Sqr()
{
    double finalIm = 2 * this->number.re * this->number.im;

    this->number.xmm = _mm_mul_pd(this->number.xmm, this->number.xmm);
    this->number.re = this->number.re - this->number.im;
    this->number.im = finalIm;

    return *this;
}

double ComplexNumber::SqrMag()
{
    _rawComplex sqr;
    sqr.xmm = _mm_mul_pd(this->number.xmm, this->number.xmm);

    return sqr.re + sqr.im;
}

ComplexNumber& ComplexNumber::Add(const ComplexNumber &c)
{
    this->number.xmm = _mm_add_pd(this->number.xmm, c.number.xmm);

    return *this;
}

ComplexNumber& ComplexNumber::Multiply(const ComplexNumber &c)
{
    double re = (this->number.re * c.number.re) - (this->number.im * c.number.im);
    double im = (this->number.re * c.number.im) + (this->number.im * c.number.re);

    this->number.xmm = _mm_setr_pd(re, im);

    return *this;
}
