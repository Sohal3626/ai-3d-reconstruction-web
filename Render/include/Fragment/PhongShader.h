//
// Created by desktop on 26. 5. 2..
//

#ifndef TOYRENDERER2_PHONGSHADER_H
#define TOYRENDERER2_PHONGSHADER_H

#include "../data/Material.h"
#include "FragmentIn.h"

class PhongShader{
public:
    const material& mtl;
    Vec3 lightPos;
    Vec3 viewPos;

    explicit PhongShader(const material& m, const Vec3 lp, const Vec3 cp) : mtl(m), lightPos(lp), viewPos(cp) {}

    Vec3 operator()(const FragmentIn& in) const {
        const Vec3 N = normalize(Vec3{in.normal.x, in.normal.y, in.normal.z});
        const Vec3 L = normalize(lightPos - in.worldPos);
        const Vec3 V = normalize(viewPos - in.worldPos);

        const Vec3 I = L * -1.0f;
        const Vec3 R = reflect(I, N);

        if (mtl.materialId == 65535) {
            const float fakeDiff = std::max(N.dot(L), 0.2f);
            const float spec = std::pow(std::max(V.dot(R), 0.0f), 64.0f);
            const Vec3 specColor = Vec3{1, 1, 1} * spec;
            const float combined = std::min(fakeDiff + spec, 1.0f);
            return Vec3{1.0f, 1.0f, 1.0f} * combined;
        }

        const float diff = std::max(N.dot(L), 0.f);

        Vec3 baseColor = mtl.diffuse;
        if (baseColor.x == 0 && baseColor.y == 0 && baseColor.z == 0) {
            baseColor = Vec3{0.5f, 0.5f, 0.5f};
        }
        const float spec = std::pow(std::max(V.dot(R), 0.0f), mtl.shininess);
        const Vec3 specColor = Vec3{1, 1, 1} * spec;

        const Vec3 result = baseColor * diff + mtl.ambient * globalAmbientIntensity + specColor;

        return Vec3{
            std::min(result.x, 1.0f),
            std::min(result.y, 1.0f),
            std::min(result.z, 1.0f)
        };
    }
private:
    const float globalAmbientIntensity = 0.5f;
    static inline Vec3 reflect(const Vec3& I, const Vec3& N) { return I - N * (2.0f * I.dot(N)); }
};

#endif //TOYRENDERER2_PHONGSHADER_H