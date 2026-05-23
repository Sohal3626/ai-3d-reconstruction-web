//
// Created by desktop on 26. 3. 19..
//

#ifndef TOYRENDERER2_MATERIAL_H
#define TOYRENDERER2_MATERIAL_H
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../library/Geometry.h"

struct alignas(16) material {
    uint16_t materialId = 65535;
    uint16_t textureId = 65535;
    int16_t illumination = 0;
    uint16_t padding0 = 0;
    float dissolve = 1.f;
    float shininess = 0.f;

    Vec3 ambient = {0.2f, 0.2f, 0.2f};
    float opticalDensity = 1.f;

    Vec3 diffuse = {0.8f, 0.8f, 0.8f};
    float padding1 = 0;

    Vec3 specular = {0.f, 0.f, 0.f};
    float padding2 = 0;

    Vec3 emission = {0.f, 0.f, 0.f};
    float padding3 = 0;
};

class Material {
public:
    bool loadMtl(const std::string &filename);
    [[nodiscard]] const material& get(const std::string &name) const {
        if (const auto it = mtls.find(name); it != mtls.end()) return it->second;
        static const material default_material;
        return default_material;
    }
private:
    std::map<std::string,material> mtls;
    std::vector<std::string> texturePaths;
};


#endif //TOYRENDERER2_MATERIAL_H