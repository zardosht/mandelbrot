#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <iostream>
#include <sstream>

const int ZOOM_FACTOR = 2;

template<typename T>
struct Point
{   
    T x;
    T y;
};

template<typename T>
struct Size
{
    T width;
    T height;
};

template<typename T>
class Window
{   

public:
    Window(T xmin, T xmax, T ymin, T ymax) : 
        _xmin{xmin}, _xmax{xmax}, 
        _ymin{ymin}, _ymax{ymax} { }

    void zoom_in() {
        _xmin /= ZOOM_FACTOR;
        _xmax /= ZOOM_FACTOR;
        _ymin /= ZOOM_FACTOR;
        _ymax /= ZOOM_FACTOR;
    };

    void zoom_out() {
        _xmin *= ZOOM_FACTOR;
        _xmax *= ZOOM_FACTOR;
        _ymin *= ZOOM_FACTOR;
        _ymax *= ZOOM_FACTOR;
    };

    T xmin() const { return _xmin; }
    T xmax() const { return _xmax; }
    T ymin() const { return _ymin; }
    T ymax() const { return _ymax; }

    std::string tostring() {
        std::stringstream ss;
        ss << _xmin << ", " << _xmax << ", " << _ymin << ", " << _ymax;
        return ss.str();
    }

private: 
    T _xmin;
    T _xmax;
    T _ymin;
    T _ymax;
};


class Mandelbrot
{
    public: 
        void draw();
        void zoom_in();
        void zoom_out();

    private: 
        Window<double> _domain {-1.5, 1.5, -1.5, 1.5};
        Size<int> _image_size {0, 0};
        Point<int> _image_center {0, 0};
        int _zoom_level = 0;
};



#endif // MANDELBROT_H