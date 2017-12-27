#pragma once

// headers
#include <Mandelbrot/ComplexNumber.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// namespaces
using sf::Image;
using sf::Color;
using std::string;
using std::vector;

// classes
class Mandelbrot
{
private:
    // members
    Image image;
    size_t width;
    size_t height;
    ComplexNumber xScale;
    ComplexNumber yScale;
    size_t iterations;
    vector<Color> colorPalette;

public:
    // constructors
    Mandelbrot(size_t width, size_t height, ComplexNumber &xSet, ComplexNumber &ySet, size_t iterations, size_t colorPaletteSize);
    Mandelbrot(size_t width, size_t height, ComplexNumber &pointOfInterest, double zoom, size_t iterations, size_t colorPaletteSize);
    Mandelbrot();

    // destructors
    ~Mandelbrot();

    // methods
    void Generate();
    bool Save(const string &path);

private:
    // private methods
    size_t ComputePixel(ComplexNumber &z, double x, double y);
    Color ColoratePixel(ComplexNumber &z, size_t iters);
    Color HsvToRgb(double h, double s, double v);
    Color Lerp(Color a, Color b, double step);
    double Map(double x, double in_min, double in_max, double out_min, double out_max);
    double ScaleX(int v);
    double ScaleY(int v);
};
