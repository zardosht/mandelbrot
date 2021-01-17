#include <iostream>

#include "mandelbrot.h"


int main()
{
    Mandelbrot mb;
    mb.draw();
    mb.zoom_in();
    mb.zoom_in();
    mb.zoom_out();
    mb.zoom_out();
}
