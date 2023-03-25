#pragma once
#include <iostream>
#include <vector>
#include "../primitives/Color.h"

class Canvas
{
private:
    int m_width;
    int m_height;
    // std::vector<std::vector<Color>> m_pixels;
    std::vector<Color> m_pixels;
    // int clamp_pixels(double value, int max_val = 255, int min_val = 0);

public:
    Canvas(int width, int height,const Color& color = Color(0,0,0));

    int width(){return m_width;}
    int height(){return m_height;}
    Color& pixel_at(int row, int col);
    void write_pixel(int row, int col, const Color& color);
    std::vector<Color>& pixels(){return m_pixels;}
    int clamp_pixels(double value, int max_val, int min_val);
    std::string canvas_to_ppm();

    ~Canvas() = default;
};


