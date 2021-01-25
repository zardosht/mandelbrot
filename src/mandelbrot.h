#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <iostream>
#include <sstream>
#include <complex>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>



// const int ZOOM_FACTOR = 2;
const double ZOOM_FACTOR = 1.2;

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
        _ymin{ymin}, _ymax{ymax}, 
        _size{std::abs(xmax - xmin), std::abs(ymax - ymin)}, 
        _center{(xmin + xmax) / 2, (ymin + ymax) / 2}  {  }

    Window(Size<T> size, Point<T> center);

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

    T width() const { return _size.width; }
    T height() const { return _size.height; }
    Size<T> size() const { return _size; }

    T xmin() const { return _xmin; }
    T xmax() const { return _xmax; }
    T ymin() const { return _ymin; }
    T ymax() const { return _ymax; }

    Point<T> center() const { return _center; }
    void set_center(Point<T> center);

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
    Size<T> _size;
    Point<T> _center;
};


class Mandelbrot
{
    public: 
        Mandelbrot(Size<int> im_size, Point<int> center) : _image_size{im_size}, _image_center{center} { }

        void draw(cv::Mat& image);
        void zoom_in();
        void zoom_out();

        void set_image_center(const int x, const int y) { 
            std::cout << "set_image_center(), x=" << x << ", y=" << y << std::endl;
            _image_center.x = x;  
            _image_center.y = y;    
        }

        Point<int> get_image_center() const { return _image_center; }

    private: 
        std::vector<Window<int>> segment_image(cv::Mat& image);
        int get_num_iterations(std::complex<double> c);
        std::complex<double> pixel_to_frac_domain(int i, int j);
        cv::Vec3b get_color(int num_iter);

        Window<double> _domain {-1.5, 1.5, -1.5, 1.5};
        // Window<double> _domain {-3, 3, -3, -3};
        Size<int> _image_size {0, 0};
        Point<int> _image_center {0, 0};
        int _zoom_level = 0;
        int _max_iter = 50;
        double _escape_limit = 2.0;
};



#endif // MANDELBROT_H