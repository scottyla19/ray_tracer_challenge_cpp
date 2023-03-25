#include "Canvas.h"
#include <sstream>
#include <iostream>
#include <string>
#include <string_view>
#include <cmath>

Canvas::Canvas(int width, int height, const Color& color){
    m_width = width;
    m_height = height;
    m_pixels.resize(width*height);
    std::fill(m_pixels.begin(), m_pixels.end(), color);
}

Color& Canvas::pixel_at(int row, int col){
    return m_pixels[row*m_width + col];
}

void Canvas::write_pixel(int row, int col, const Color& color){
    m_pixels[row*m_width + col] = color;
}
int Canvas::clamp_pixels(double value, int max_val = 255, int min_val = 0){
    int scaled_val = round(value*max_val);
    if (scaled_val > max_val) {
        scaled_val = max_val;
    }
    if  (scaled_val < min_val){
        scaled_val = min_val;
    }
    return scaled_val;
}

std::string Canvas::canvas_to_ppm(){
    std::ostringstream header_stream;
    header_stream << "\nP3\n" << m_width << " " << m_height << "\n" << "255\n";
    std::string ppm = header_stream.str();
    std::ostringstream ss;
    for (int i = 0; i < m_height*m_width; i++)
    {
        int row = floor(double(i) / m_width);
        int col = i % m_width;
        Color& color = pixel_at(row, col);
        ss << "" << clamp_pixels(color.red()) << " " << clamp_pixels(color.green()) << " " << clamp_pixels(color.blue()) << " ";
        if (col == m_width - 1){
            ss.seekp(-1, ss.cur);
            ss << "\n";
        }
    }

    ppm += ss.str();
    std::string_view sv = ppm;

    return std::string(sv);
}
