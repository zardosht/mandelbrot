#include <iostream>

#include "mandelbrot.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


using std::cout;
using std::endl;

int main()
{
    int height = 512;
    int width = 512;
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    Size<int> im_size;
    im_size.height = height;
    im_size.width = width;
    Point<int> im_center;
    im_center.x = width / 2;
    im_center.y = height / 2;
    Mandelbrot mb(im_size, im_center);
    mb.draw(image);
    mb.zoom_in();
    mb.zoom_out();

    cout << "OpenCV Version used:" << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl;
    cv::imshow("Mandelbrot", image);
    int k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 'q')
    {
        cv::destroyAllWindows();
    }
    return 0;

}
