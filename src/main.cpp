#include <iostream>

#include "mandelbrot.h"

#include "/usr/local/include/opencv4/opencv2/core.hpp"


using std::cout;
using std::endl;

int main()
{
    int height = 512;
    int width = 512;
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    Mandelbrot mb;
    mb.draw(image);
    mb.zoom_in();
    mb.zoom_out();

    // cout<<"OpenCV Version used:"<< CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl;

}
