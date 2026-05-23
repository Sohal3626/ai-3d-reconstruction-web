//
// Created by desktop on 26. 5. 8..
//

#ifndef TOYRENDERER2_FLATSHADER_H
#define TOYRENDERER2_FLATSHADER_H

//
// Created by desktop on 26. 5. 2..
//

#include "../data/Material.h"
#include "FragmentIn.h"

class FlatShader{
public:
    const material& mtl;
    Vec3 lightPos;

    explicit FlatShader(const material& m, const Vec3 lp, const Vec3 placeHolder) : mtl(m), lightPos(lp) {}

    Vec3 operator()(const FragmentIn& in) const {
        const Vec3 L = normalize(lightPos-in.worldPos);
        if (mtl.materialId == 65535) {
            const float fakeDiff = std::max(in.faceNormal.dot(L), 0.2f);
            return Vec3{1.0f, 1.0, 1.0f} * fakeDiff;
        }

        Vec3 baseColor = mtl.diffuse;
        if (baseColor.x == 0 && baseColor.y == 0 && baseColor.z == 0) {
            baseColor = Vec3{0.5f, 0.5f, 0.5f};
        }

        const float intensity = std::max(in.faceNormal.dot(L), 0.0f);
        return baseColor * intensity + mtl.ambient * globalAmbientIntensity;
    }
private:
    const float globalAmbientIntensity = 0.5f;
};
#endif //TOYRENDERER2_FLATSHADER_H