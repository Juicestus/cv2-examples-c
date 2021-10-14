#include "colorutils/colorutils.hpp"

#include <iostream>

int main() {
    colorutils::RGB rgb = colorutils::RGB(255, 0, 0);
    colorutils::HSV hsv = rgb.getAsHSV();
    std::printf("HSV(%.3f, %.3f, %.3f)", hsv.H(), hsv.S(), hsv.V());
}
