/**
 * Header library for color utilities.
 * 
 * (c) Justus Languell, 2021
 * 
 */

#ifndef _COLOR_UTILS_RGB_HPP_
#define _COLOR_UTILS_RGB_HPP_

#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>

#include "hsv.hpp"

namespace colorutils {

typedef struct {
    double r;
    double g;
    double b;
} C_RGB;

C_RGB NewC_RGB(double r, double g, double b) {
    C_RGB rgb;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return rgb;
}

class RGB {
private:
    double r, g, b;
    std::invalid_argument badInput(char c) {
        return std::invalid_argument("[ERROR] \""
            + std::string(1, c) + " value must either be\n"
            + " * a fraction between 0 and 1\n"
            + " * a value between 0 and 255\n"
        );
    }

public:
    RGB(double r, double g, double b) {
        if (r < 0 || r > 255) throw badInput('r');
        if (g < 0 || g > 255) throw badInput('g');
        if (b < 0 || b > 255) throw badInput('b');

        if (r > 1.0) r /= 255;
        if (g > 1.0) g /= 255;
        if (b > 1.0) b /= 255;

        this->r = r;
        this->g = g;
        this->b = b;
    }

    colorutils::HSV getAsHSV() {
        double h, s, v;
        double min, max, delta;

        min = this->r < this->g ? this->r : this->g;
        min = min  < this->b ? min  : this->b;

        max = this->r > this->g ? this->r : this->g;
        max = max  > this->b ? max  : this->b;

        v = max;
        delta = max - min;

        if (delta < 0.00001) return colorutils::HSV(0, 0, v);

        if (max > 0.0) s = delta / max;
        else return colorutils::HSV(std::nan("Caught divide by zero"), 0, v);

        if (this->r >= max) h = (this->g - this->b) / delta;
        else if (this->g >= max) h = 2.0 + (this->b - this->r) / delta;
        else h = 4.0 + (this->r - this->g) / delta;

        h *= 60.0;
        if (h < 0.0) h += 360.0;

        return colorutils::HSV(h, s, v);
    }

    double R() { return this->r; }
    double G() { return this->g; }
    double B() { return this->b; }

    double getR() { return R(); }
    double getG() { return G(); }
    double getB() { return B(); }

    double getRed() { return R(); }
    double getGreen() { return G(); }
    double getBlue() { return B(); }

    RGB operator+(RGB other) {
        return RGB(
            this->r + other.r,
            this->g + other.g,
            this->b + other.b
        );
    }

    RGB operator-(RGB other) {
        return RGB(
            this->r - other.r,
            this->g - other.g,
            this->b - other.b
        );
    }

    RGB operator+(colorutils::HSV other) {
        return *this + other.getAsRGB();
    }

    RGB operator-(colorutils::HSV other) {
        return *this - other.getAsRGB();
    }

    C_RGB getAsC_RGB() {
        return NewC_RGB(this->r, this->g, this->b);
    }
};

}

#endif
