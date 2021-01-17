#include<iostream>


#include "mandelbrot.h"




void Mandelbrot::draw()
{
    std::cout << "Mandelbrot::draw() called" << std::endl;
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





// Mandlebrot. img_height, img_width, img_center, xmin, xmax, ymin, ymax, zoom_level, draw(), zoom_in(), zoom_out()
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

