//
// Created by desktop on 26. 3. 29..
//

#ifndef TOYRENDERER2_CANVAS_H
#define TOYRENDERER2_CANVAS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "../include/library/Geometry.h"

struct Canvas {
    const int width = 0, height = 0;
    std::vector<Vec3> pixels;
    std::vector<float> depthBuffer;

    Canvas(const int w, const int h) : width(w), height(h) {
        pixels.resize(width * height);
        depthBuffer = std::vector<float>(width * height, std::numeric_limits<float>::max());

    }

    void setPixel(const int x, const int y, const Vec3 &color) {
        if (!(x >= 0 && x < width && y >= 0 && y < height)) return;
        const int idx = width * y + x;
        pixels[idx] = color;
    }

    void save_ppm(const std::string &filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file! " << filename << std::endl;
            return;
        }
        file << "P3\n" << width << " " << height << "\n255\n";

        for (const auto& p : pixels) {
            file << static_cast<int>(255.99 * p.x) << " "
                << static_cast<int>(255.99 * p.y) << " "
                << static_cast<int>(255.99 * p.z) << "\n";
        }
    }

    [[nodiscard]] uint8_t* getRGBABuffer() const {
        static std::vector<uint8_t> buffer;
        buffer.clear();
        for (const auto& p : pixels) {
            buffer.push_back(static_cast<uint8_t>(255.99 * p.x));
            buffer.push_back(static_cast<uint8_t>(255.99 * p.y));
            buffer.push_back(static_cast<uint8_t>(255.99 * p.z));
            buffer.push_back(255);
        }
        return buffer.data();
    }
};

#endif //TOYRENDERER2_CANVAS_H