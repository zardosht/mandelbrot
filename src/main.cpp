#include <iostream>

#include "mandelbrot.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


using std::cout;
using std::endl;


void on_mouse_down(int event, int x, int y, int flags, void *userdata) {
  /// capture movements of the mouse cursor to get pixels which it points to.
  if (event == cv::EVENT_LBUTTONDOWN) {
      static_cast<Mandelbrot*>(userdata)->set_image_center(x + 100, y);
  }
}


int main()
{
    int height = 512;
    int width = 512;
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    Size<int> im_size;
    im_size.height = height;
    im_size.width = width;
    Point<int> im_center;
    // im_center.x = width / 2;
    im_center.x = width / 2 + 100;
    im_center.y = height / 2;
    Mandelbrot mb(im_size, im_center);
    mb.draw(image);

    cout << "OpenCV Version used:" << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl;
    std::string window_name = "Mandelbrot";
    cv::imshow(window_name, image);
    cv::setMouseCallback(window_name, on_mouse_down, &mb);

    int k = cv::waitKey(0); // Wait for a keystroke in the window
    while (k != 'q') {
        if (k == 'i') {
            mb.zoom_in();
            mb.draw(image);
        } else if (k == 'o') {
            mb.zoom_out();
            mb.draw(image);
        }
        cv::imshow(window_name, image);
        k = cv::waitKey(0); // Wait for a keystroke in the window
    }

    cv::destroyAllWindows();
    return 0;

}
