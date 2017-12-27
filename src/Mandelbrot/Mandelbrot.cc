// headers
#include <Mandelbrot/Mandelbrot.hpp>
#include <cmath>

// constructors
Mandelbrot::Mandelbrot(size_t width, size_t height, ComplexNumber &xSet, ComplexNumber &ySet, size_t iterations, size_t colorPaletteSize)
{
    this->width = width;
    this->height = height;
    this->xScale = xSet;
    this->yScale = ySet;
    this->iterations = iterations;

    for(size_t i = 0; i < colorPaletteSize; i++)
    {
        double h = this->Map(i, 0, colorPaletteSize, 0, 360);
        double s = this->Map(i, 0, colorPaletteSize, 0, 1);
        double v = this->Map(i, 0, colorPaletteSize, 0.05, 0.8);

        this->colorPalette.push_back(this->HsvToRgb(h, s, v));
    }

    this->image.create(width, height, Color::Black);
}

Mandelbrot::Mandelbrot(size_t width, size_t height, ComplexNumber &pointOfInterest, double zoom, size_t iterations, size_t colorPaletteSize)
{


    this->width = width;
    this->height = height;
    //this->xScale = xSet;
    //this->yScale = ySet;
    this->iterations = iterations;

    for(size_t i = 0; i < colorPaletteSize; i++)
    {
        double h = this->Map(i, 0, colorPaletteSize, 0, 360);
        double s = this->Map(i, 0, colorPaletteSize, 1, 0);
        double v = this->Map(i, 0, colorPaletteSize, 0, 1);

        this->colorPalette.push_back(this->HsvToRgb(h, s, v));
    }

    this->image.create(width, height, Color::Black);
}

Mandelbrot::Mandelbrot()
{
    this->width = 640;
    this->height = 480;
    this->xScale = ComplexNumber(-2.5, 1);
    this->yScale = ComplexNumber(-1, 1);
    this->iterations = 100;

    for(size_t i = 0; i < 500; i++)
    {
        double h = this->Map(i, 0, 500, 0, 360);
        double s = this->Map(i, 0, 500, 1, 0);
        double v = this->Map(i, 0, 500, 0, 1);

        this->colorPalette.push_back(this->HsvToRgb(h, s, v));
    }


    this->image.create(width, height, Color::Black);
}

// destructors
Mandelbrot::~Mandelbrot()
{
}

// methods
void Mandelbrot::Generate()
{
    for(int y = 0; y < this->height; y++)
    {
        for(int x = 0; x < this->width; x++)
        {
            ComplexNumber z;

            size_t iters = this->ComputePixel(z, x, y);
            Color color = this->ColoratePixel(z, iters);

            this->image.setPixel(x, y, color);
        }
    }
}

bool Mandelbrot::Save(const std::string &path)
{
    return this->image.saveToFile(path);
}

// private methods
size_t Mandelbrot::ComputePixel(ComplexNumber &z, double x, double y)
{
    size_t currentIteration = 0;
    ComplexNumber c(this->ScaleX(x), this->ScaleY(y));

    while((z.SqrMag() < (1 << 16)) && (currentIteration < this->iterations))
    {
        z = z.Sqr();
        z.Add(c);
        currentIteration++;
    }

    return currentIteration;
}

Color Mandelbrot::ColoratePixel(ComplexNumber &z, size_t iters)
{
    if(iters < this->iterations)
    {
        double log_zn = log(z.SqrMag()) / 2;
        double nu = log(log_zn / log(2)) / log(2);

        iters += 1 - nu;
    }

    Color a = this->colorPalette[floor(iters)];
    Color b = this->colorPalette[floor(iters >> 2)];
    Color f =this->Lerp(a, b, (iters / (this->iterations / 50)));

    return f;
}

Color Mandelbrot::Lerp(Color a, Color b, double step)
{
    uint8_t ar = a.r;
    uint8_t ag = a.g;
    uint8_t ab = a.b;

    uint8_t br = b.r;
    uint8_t bg = b.g;
    uint8_t bb = b.b;

    uint8_t red = ar + step * (br - ar);
    uint8_t green = ag + step * (bg - ag);
    uint8_t blue = ab + step * (bb - ab);

    return Color(red, green, blue);
}

double Mandelbrot::ScaleX(int v)
{
    return this->xScale.Im() + (v * (this->xScale.Re() - this->xScale.Im()) / this->width);
}

double Mandelbrot::ScaleY(int v)
{
    return this->yScale.Im() + (v * (this->yScale.Re() - this->yScale.Im()) / this->height);
}

Color Mandelbrot::HsvToRgb(double h, double s, double v)
{
    double r = 0;
    double g = 0;
    double b = 0;
    double c = v * s;
    double hPrime = fmod(h / 60.0, 6);
    double x = c * (1 - fabs(fmod(hPrime, 2) - 1));
    double m = v - c;

    if(0 <= hPrime && hPrime < 1)
    {
        r = c;
        g = x;
        b = 0;
    }

    else if(1 <= hPrime && hPrime < 2)
    {
        r = x;
        g = c;
        b = 0;
    }

    else if(2 <= hPrime && hPrime < 3)
    {
        r = 0;
        g = c;
        b = x;
    }

    else if(3 <= hPrime && hPrime < 4)
    {
        r = 0;
        g = x;
        b = c;
    }

    else if(4 <= hPrime && hPrime < 5)
    {
        r = x;
        g = 0;
        b = c;
    }

    else if(5 <= hPrime && hPrime < 6)
    {
        r = c;
        g = 0;
        b = x;
    }

    else
    {
        r = 0;
        g = 0;
        b = 0;
    }

    r += m;
    g += m;
    b += m;

    return Color(r * 255, g * 255, b * 255);
}

double Mandelbrot::Map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
