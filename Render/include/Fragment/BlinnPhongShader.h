//
// Created by Sohal03 on 26. 5. 8..
//

#ifndef TOYRENDERER2_BLINNPHONGSHADER_H
#define TOYRENDERER2_BLINNPHONGSHADER_H

#include "FragmentIn.h"
#include "../library/Geometry.h"
#include "../VertexShader.h"

class BlinnPhongShader {
public:
    const material& mtl;
    Vec3 lightPos;
    Vec3 viewPos;

    explicit BlinnPhongShader(const material& m, const Vec3 lp, const Vec3 cp) : mtl(m), lightPos(lp), viewPos(cp) {}

    Vec3 operator()(const FragmentIn& in) const {
        const Vec3 worldPos = Vec3{in.worldPos.x, in.worldPos.y, in.worldPos.z};
        const Vec3 N = normalize(Vec3{in.normal.x, in.normal.y, in.normal.z});
        const Vec3 L = normalize(lightPos - worldPos);
        const Vec3 V = normalize(viewPos - worldPos);

        if (mtl.materialId == 65535) {
            const float fakeDiff = std::max(N.dot(L), 0.2f);
            const Vec3 H = normalize(L + V);
            const float specular = std::pow(std::max(N.dot(H), 0.0f), 64.0f);
            const float combined = std::min(fakeDiff + specular, 1.0f);
            return Vec3{1.0f, 1.0f, 1.0f} * combined;
        }

        const float diff = std::max(N.dot(L), 0.f);
        const Vec3 H = normalize(L + V);
        const float specular = pow(std::max(N.dot(H), 0.0f), mtl.shininess);

        Vec3 baseColor = mtl.diffuse;
        if (baseColor.x == 0 && baseColor.y == 0 && baseColor.z == 0) {
            baseColor = Vec3{0.5f, 0.5f, 0.5f};
        }
        const Vec3 specColor = Vec3{1.0f, 1.0f, 1.0f} * specular;
        const Vec3 result = baseColor * diff + mtl.ambient * globalAmbientIntensity + specColor;

        return Vec3{
            std::min(result.x, 1.0f),
            std::min(result.y, 1.0f),
            std::min(result.z, 1.0f)
        };
    }
private:
    const float globalAmbientIntensity = 0.5f;
};

#endif //TOYRENDERER2_BLINNPHONGSHADER_H