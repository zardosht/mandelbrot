#include <iostream>
#include <thread>


#include "mandelbrot.h"


using std::vector;


void Mandelbrot::draw(cv::Mat& image)
{
    std::cout << "Mandelbrot::draw()" << std::endl;
    vector<Window<int>> segments = segment_image(image);
    for (auto& seg : segments) {
        for (int j = seg.xmin(); j < seg.xmax(); ++j) {
            for (int i = seg.ymin(); i < seg.ymax(); ++i) {
                // i is y (row) and j is x (column) in the matrix
                std::complex<double> c = pixel_to_frac_domain(j, i);
                int num_iter = get_num_iterations(c);
                cv::Vec3b color = get_color(num_iter);
                image.at<cv::Vec3b>(i, j) = color;
            }
        }
    }
}


std::complex<double> Mandelbrot::pixel_to_frac_domain(int x, int y) 
{
    // x and y are in image space. x is column (j) and y is row (i) in the matrix
    double x_scaled = ((x - _image_center.x) * _domain.width()) / _image_size.width;
    double y_scaled = ((y - _image_center.y) * _domain.height()) / _image_size.height;
    return std::complex<double>(x_scaled, y_scaled);
}

cv::Vec3b Mandelbrot::get_color(int num_iter)
{
    // from here: https://stackoverflow.com/a/35749415/228965
    cv::Vec3f hsv;   // hue, saturation, value; hue has range [0, 179] in OpenCV
    hsv[0] = static_cast<float>(180 * num_iter) / _max_iter; 
    hsv[1] = 255.0;
    hsv[2] = (num_iter == 0) ? 0.0 : 255.0;

    cv::Mat_<cv::Vec3f> hsvMat(hsv);
    cv::Mat_<cv::Vec3f> bgrMat;
    cv::cvtColor(hsvMat, bgrMat, cv::COLOR_HSV2BGR);
    bgrMat *= 255; // Upscale after conversion
    // Conversion to Vec3b is handled by OpenCV, no need to static_cast
    return bgrMat(0);
}

int Mandelbrot::get_num_iterations(std::complex<double> c)
{
    int num_iter = 0;
    std::complex<double> z(0, 0);
    std::complex<double> zero(0, 0);
    while (abs(z) <= _escape_limit && num_iter < _max_iter) {
        z = z * z + c;
        if (z == zero) {
            return 0;
        }
        num_iter++;
    }
    return num_iter;
}

std::vector<Window<int>> Mandelbrot::segment_image(cv::Mat& image)
{
    int num_cores = std::thread::hardware_concurrency();
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
    _zoom_level++;
    std::cout << "zoom_in(), zoom_level=" << _zoom_level << std::endl;
    _domain.zoom_in();
    std::cout << "Domain: " << _domain.tostring() << std::endl;
}

void Mandelbrot::zoom_out()
{
    if (_zoom_level == 0) {
        std::cout << "zoom_out(), zoom_level=0, retrun;" << std::endl;
        return;
    }
    _zoom_level--;
    std::cout << "zoom_out(), zoom_level=" << _zoom_level << std::endl;
    _domain.zoom_out();
    std::cout << "Domain: " << _domain.tostring() << std::endl;
    if (_zoom_level == 0) {
        set_image_center(_image_size.width / 2 + 100, _image_size.height / 2);
    }
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

