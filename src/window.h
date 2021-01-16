#ifndef WINDOW__H
#define WINDOW__H

template<typename T>
class Window {
    T _x_min, _x_max, _y_min, _y_max;

public:
    Window(T x_min, T x_max, T y_min, T y_max):
        _x_min(x_min), 
        _x_max(x_max), 
        _y_min(y_min), 
        _y_max(y_max) { }
 
    // Utility functions for getting the size, width and height of the window
 	T size() {
 		return (width() * height());
 	}
 
 	T width() {
 		return (_x_max - _x_min);
 	}
 
 	T height() {
 		return (_y_max - _y_min);
 	}

    // Getters
    T xmin() const { return _x_min; }
    T xmax() const { return _x_max; }
    T ymin() const { return _y_min; }
    T ymax() const { return _y_max; }
 
    // Reset all values
 	void reset(T x_min, T x_max, T y_min, T y_max) {
 		_x_min = x_min;
        _x_max = x_max;
        _y_min = y_min;
        _y_max = y_max;
 	}
};


#endif
