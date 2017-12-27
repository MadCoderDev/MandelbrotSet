// headers
#include <iostream>
#include <Mandelbrot/Mandelbrot.hpp>

// main
int main()
{
    ComplexNumber X(1, -2.5);
    ComplexNumber Y(1, -1);
    ComplexNumber xOffset(0, 0);
    ComplexNumber yOffset(0, 0);
    ComplexNumber xScale(1, 0);
    ComplexNumber yScale(1, 0);
    size_t WIDTH = 1920;
    size_t HEIGHT = 1080;
    size_t ITERS = 5000;

    Mandelbrot mandelbrot(WIDTH, HEIGHT, X.Add(xOffset).Multiply(xScale), Y.Add(yOffset).Multiply(yScale), ITERS, 500);
    mandelbrot.Generate();
    mandelbrot.Save("img.png");

    return EXIT_SUCCESS;
}
