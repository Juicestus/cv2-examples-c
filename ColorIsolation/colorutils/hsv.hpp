/**
 * Header library for color utilities.
 * 
 * (c) Justus Languell, 2021
 * 
 */

#ifndef _COLOR_UTILS_HSV_HPP_
#define _COLOR_UTILS_HSV_HPP_

#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>

#include "rgb.hpp"

namespace colorutils {

typedef struct {
    double h;
    double s;
    double v;
} C_HSV;

C_HSV NewC_HSV(double h, double s, double v) {
    C_HSV hsv;
    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
    return hsv;
}

class HSV {
private:
    double h, s, v;
    std::invalid_argument badInput(char c, bool h) {
        return std::invalid_argument("[ERROR] \""
            + std::string(1, c) + " value must be\n"
            + (!h ? " * a fraction between 0 and 1\n"
            : "* an angle from 0 to 360\n")
        );
    }

public:
    HSV(double h, double s, double v) {
        if (h < 0 || h > 360) throw badInput('h', true);
        if (s < 0 || s > 1) throw badInput('s', false);
        if (v < 0 || v > 1) throw badInput('v', false);

        this->h = h;
        this->s = s;
        this->v = v;
    }

    colorutils::RGB getAsRGB() {
        double hh, p, q, t, ff;
        long i;

        if (this->s <= 0) return colorutils::RGB(this->v, this->v, this->v);
        hh = this->h;
        if (hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long) hh;
        p = this->v * (1.0 - this->s);
        q = this->v * (1.0 - this->s * ff);
        t = this->v * (1.0 - this->s * (1.0 - ff));

        switch (i) {
            case  0: return colorutils::RGB(this->v, t, p);
            case  1: return colorutils::RGB(q, this->v, p);
            case  2: return colorutils::RGB(p, this->v, t);
            case  3: return colorutils::RGB(p, q, this->v);
            case  4: return colorutils::RGB(t, p, this->v);
            case  5: return colorutils::RGB(this->v, p, q);
            default: return colorutils::RGB(this->v, p, q);
        }
    }

    double H() { return this->h; }
    double S() { return this->s; }
    double V() { return this->v; }

    double getH() { return H(); }
    double getS() { return S(); }
    double getV() { return V(); }

    double getHue() { return H(); }
    double getSaturation() { return S(); }
    double getValue() { return V(); }

    HSV operator+(HSV other) {
        return HSV(
            this->h + other.h,
            this->s + other.s,
            this->v + other.v
        );
    }

    HSV operator-(HSV other) {
        return HSV(
            this->h - other.h,
            this->s - other.s,
            this->v - other.v
        );
    }

    HSV operator+(colorutils::RGB other) {
        return *this + other.getAsHSV();
    }

    HSV operator-(colorutils::RGB other) {
        return *this - other.getAsHSV();
    }

    C_HSV getAsC_HSV() {
        return NewC_HSV(this->h, this->s, this->v);
    }
};

}

#endif