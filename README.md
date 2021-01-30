# mandelbrot
This is the Capstone project of Udacity's C++ Nanodegree. 
The `mandelbort` program draws a [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) on an image with size given by user.
The image size must be one of the values 128, 256, 512, 1024. User can zoom in and zoom out in the image and select the center point for zooming. 

### Controls: 
* `i`: zoom in
* `o`: zoom out
* `q`: close window and quit
* `mouse click`: set center point for zooming 


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* OpenCV >= 4.1 https://opencv.org/


## Build and Run Instructions
1. create a `build` folder in the root `mandelbrot` folder
2. `cd build && cmake ..`
3. `make`
4. `./mandelbrot`


## File Structure
The project consists of the following files:
- `main.cpp` - Interface between user and OpenCV. Created a `cv::Mat` for the image. Receives user's input for zooming in and out and setting the center point for zooming. Creates an instance of `Mandelbrot` class and passes user's commands to it. 
- `mandelbrot.h` - Header file for `Mandelbrot` and some auxillary classes. Inspired by [this blog post](https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/), the `Mandelbrot` class uses a `Window` class for managing the domain of the Mandelbrot set and the drawn image and conversion between image space (pixel coordinates) and current domain of Mandelbrot set. The `Window` class also takes care of changing the domain of Mandelbrot set when zooming in and out. 
- `mandelbort.cpp` - Implementation of `Mandelbrot` class. We use the simple [escape time algorithm](https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings) for drawing the image. The image (a `cv::Mat` instance) is separated into segments (as much as CPU cores (`std::thread::hardware_concurrency()`)). The `Mandelbrot:::draw()` method then uses threads to calculate number of iterations for each point and setting the corresponding pixel color in image segment. 

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Capstone`.
5. Follow the instructions.
6. View generated images in the `/build/` folder.

