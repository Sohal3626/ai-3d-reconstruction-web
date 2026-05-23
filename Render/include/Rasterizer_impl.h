//
// Created by desktop on 26. 3. 29..
//

#ifndef TOYRENDERER2_RASTERIZER_H
#define TOYRENDERER2_RASTERIZER_H

#include "../include/Canvas.h"
#include "../include/VertexShader.h"

template <typename FragmentShaderType>
void fillTriangle(Canvas& canvas, std::span<const TFVertex, 3> pts, const FragmentShaderType& shader, Vec3 faceNormal);

#include "../src/Rasterizer_impl.hpp"
#endif //TOYRENDERER2_RASTERIZER_H