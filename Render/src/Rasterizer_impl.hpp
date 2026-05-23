//
// Created by Sohal03 on 26. 3. 31..
//
#pragma once
#include "../include/Rasterizer_impl.h"
#include "../include/Canvas.h"
#include "../include/VertexShader.h"
#include "../include/Fragment/FragmentIn.h"
#include <span>
#include <atomic>

using namespace std;

template <typename FragmentShaderType>
void fillTriangle(Canvas& canvas, const span<const TFVertex, 3> pts, FragmentShaderType& shader, const Vec4 faceNormal) {
    const int w = canvas.width;

    float minX = pts[0].position.x, maxX = pts[0].position.x;
    float minY = pts[0].position.y, maxY = pts[0].position.y;

    for (size_t i = 1; i < pts.size(); i++) {
        minX = min(minX, pts[i].position.x);
        minY = min(minY, pts[i].position.y);
        maxX = max(maxX, pts[i].position.x);
        maxY = max(maxY, pts[i].position.y);
    }

    const int xStart = max(0, static_cast<int>(floor(minX)));
    const int xEnd = min(canvas.width - 1, static_cast<int>(ceil(maxX)));
    const int yStart = max(0, static_cast<int>(floor(minY)));
    const int yEnd = min(canvas.height - 1, static_cast<int>(ceil(maxY)));

    const Vec2 tri[3] = {
        Vec2 {pts[0].position.x, pts[0].position.y},
        Vec2 {pts[1].position.x, pts[1].position.y},
        Vec2 {pts[2].position.x, pts[2].position.y}
    };

    for (int i = yStart; i <= yEnd; i++) {
        for (int j = xStart; j <= xEnd; j++) {
            const int idx = i * w + j;
            const Vec3 bary = barycentric(Vec2{static_cast<float>(j), static_cast<float>(i)}, tri);
            FragmentIn in;
            in.worldPos = pts[0].worldPos * bary.x + pts[1].worldPos * bary.y + pts[2].worldPos * bary.z;
            in.normal = pts[0].normal * bary.x + pts[1].normal * bary.y + pts[2].normal * bary.z;
            in.texCoord = pts[0].texCoord * bary.x + pts[1].texCoord * bary.y + pts[2].texCoord * bary.z;
            in.faceNormal = faceNormal;

            const float depth = pts[0].position.z * bary.x + pts[1].position.z * bary.y + pts[2].position.z * bary.z;
            if (bary.x < 0 || bary.y < 0 || bary.z < 0) continue;

            std::atomic_ref<float> target_depth(canvas.depthBuffer[idx]);

            float old_depth = target_depth.load(memory_order_relaxed);
            while (depth <= old_depth) {
                if (target_depth.compare_exchange_weak(
                    old_depth, depth, memory_order_release, memory_order_relaxed)) {
                    const Vec3 color = shader(in);
                    // cout << color.x << color.y << color.z << endl;
                    canvas.setPixel(j, i, color);
                    break;
                }
            }
        }
    }
}