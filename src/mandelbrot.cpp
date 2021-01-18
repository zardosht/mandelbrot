#include <iostream>
#include <thread>


#include "mandelbrot.h"


using std::vector;


void Mandelbrot::draw(cv::Mat& image)
{
    std::cout << "Mandelbrot::draw() called" << std::endl;
    vector<Window<int>> segments = segment_image(image);
    for (auto& seg : segments) {
        std::cout << seg.tostring() << std::endl;


    }
}

int Mandelbrot::get_num_iterations(std::complex<double> c)
{
    int num_iter = 0;
    std::complex<double> z(0, 0);
    std::complex<double> zero(0, 0);
    while (abs(z) <= _escape_limit && num_iter < _max_iter) {
        z = z * z + c;
        if (z == zero) {
            return num_iter;
        }
        num_iter++;
    }
    return num_iter;
}

std::vector<Window<int>> Mandelbrot::segment_image(cv::Mat& image)
{
    int num_cores = std::thread::hardware_concurrency();
    std::cout << "num_cores = " << num_cores << std::endl;
    vector<Window<int>> segments;
    int segment_height = image.rows / 2;
    int segment_width = image.cols / (num_cores / 2);
    for (int i = 0; i < num_cores / 2; ++i) {
        int xmin = i * segment_width;
        int xmax = i * segment_width + segment_width;
        Window<int> seg1(xmin, xmax, 0, segment_height);
        segments.push_back(seg1);
        Window<int> seg2(xmin, xmax, segment_height, image.cols);
        segments.push_back(seg2);
    }
    
    return segments;
}

void Mandelbrot::zoom_in() 
{
    std::cout << "Mandelbrot::zoom_in() called" << std::endl;
    _domain.zoom_in();
    std::cout << "Domain: " << _domain.tostring() << std::endl;

}

void Mandelbrot::zoom_out()
{
    std::cout << "Mandelbrot::zoom_out() called" << std::endl;
    _domain.zoom_out();
    std::cout << "Domain: " << _domain.tostring() << std::endl;
}





// Mandelbrot. img_height, img_width, img_center, xmin, xmax, ymin, ymax, zoom_level, draw(), zoom_in(), zoom_out()
//            draw(Mat image)  {
//                    Partition image (Mat) into "ncores" segments (say ncores=4)
//                    start ncores threads that call Mat (create 4 different Mats? or send one Mat with x, y start end coordinates for each segment?)
//    
//                    for i, j in .... {
//                        c = scale the pixel coordinates to fractal's domain (get a corresponding complex number for this pixel coordinates and zoom level)
//                        num_iter = get_num_iterations(c)  // z = 0, c = c, till max_iter calculate z = z * z + c
//                        color = get_color(num_iter)  
//                        Mat(i, j)  = color
//                    }
//             }


// Mat image


// cv::imshow(Mat)

// up arrow = zoom in, down arrow = zoom out, mouse click at pixel sets the center, q = quit

