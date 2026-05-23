//
// Created by desktop on 26. 5. 3..
//

#ifndef TOYRENDERER2_FRAGMENTIN_H
#define TOYRENDERER2_FRAGMENTIN_H

#include <cstdint>
#include "../library/Geometry.h"

struct alignas(16) FragmentIn {
    Vec4 normal;

    Vec4 faceNormal;

    Vec3 worldPos;
    float invW;

    Vec2 texCoord;
    std::uint32_t pad[2];
};

#endif //TOYRENDERER2_FRAGMENTIN_H