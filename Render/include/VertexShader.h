//
// Created by desktop on 26. 3. 23..
//

#ifndef TOYRENDERER2_VERTEXSHADER_H
#define TOYRENDERER2_VERTEXSHADER_H
#include "data/Mesh.h"
#include "library/Geometry.h"

struct alignas(16) TFVertex {
    Vec4 position;
    Vec4 normal;

    Vec3 worldPos;
    float invW{};

    Vec2 texCoord;
    uint32_t pad2[2]{};
};

class VertexShader {
public:
    Mat44 model;
    Mat44 view;
    Mat44 projection;
    Mat44 mvp;
    Vec3 cameraWorldPos;

    VertexShader(const Mat44& model, const Mat44& view, const Mat44& projection)
    : model(model), view(view), projection(projection) {
        mvp = projection * view * model;

        const Vec3 T = {view[0][3], view[1][3], view[2][3]};
        cameraWorldPos.x = -(view[0][0] * T.x + view[1][0] * T.y + view[2][0] * T.z);
        cameraWorldPos.y = -(view[0][1] * T.x + view[1][1] * T.y + view[2][1] * T.z);
        cameraWorldPos.z = -(view[0][2] * T.x + view[1][2] * T.y + view[2][2] * T.z);
    }

    [[nodiscard]] TFVertex vertexShader(const Vertex& in) const {
        TFVertex out;
        out.position = mvp * in.position;
        const Vec4 wPos = model * in.position;
        out.worldPos = Vec3{wPos.x, wPos.y, wPos.z};
        out.normal = model * Vec4(in.normal.x, in.normal.y, in.normal.z, 0.0f);
        out.texCoord = in.texCoord;
        out.invW = (out.position.w != 0.0f) ? (1.0f / out.position.w) : 1.0f;

        return out;
    }
};

#endif //TOYRENDERER2_VERTEXSHADER_H