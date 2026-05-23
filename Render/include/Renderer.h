//
// Created by desktop on 26. 4. 6..
//

#ifndef TOYRENDERER2_RENDERER_H
#define TOYRENDERER2_RENDERER_H
#include "Canvas.h"
#include "Rasterizer_impl.h"
#include "VertexShader.h"
#include "data/Mesh.h"
#include "library/Geometry.h"
//#include <omp.h>
#include <chrono>

#include "Fragment/FragmentIn.h"

inline material defaultMtl;

template <typename FragmentShaderType>
void DrawModel(Canvas& canvas, Mesh& mesh, const Material& materials,
    const VertexShader& vertexShader, const Vec3 lightPos) {
    std::cout << "Indices Size: " << mesh.indices.size() << std::endl;

    const auto start = std::chrono::high_resolution_clock::now();

    mesh.linkMtl(materials);

    for (const auto& group : mesh.subMeshes) {
        const material& mtl = materials.get(group.mtlName);
        FragmentShaderType fShader(mtl, lightPos, vertexShader.cameraWorldPos);

        const int w = canvas.width;
        const int h = canvas.height;

        //#pragma omp parallel for
        for (size_t i = 0; i < group.indexCount; i+=3) {
            TFVertex tri[3];
            for (size_t j = 0; j < 3; j++) {
                const uint32_t vertexIndex = mesh.indices[group.indexStart + i + j];
                const Vertex& v = mesh.vertices[vertexIndex];

                tri[j] = vertexShader.vertexShader(v);

                const float invW = tri[j].invW;

                tri[j].position.x = (tri[j].position.x * invW + 1.0f) * 0.5f * static_cast<float>(w);
                tri[j].position.y = (1.0f - tri[j].position.y * invW) * 0.5f * static_cast<float>(h);
            }

            Vec3 edge1 = tri[1].worldPos - tri[0].worldPos;
            Vec3 edge2 = tri[2].worldPos - tri[0].worldPos;
            Vec3 faceNormal = edge1.cross(edge2);
            if (faceNormal.z <= 0) {
                continue;
            }
            faceNormal = normalize(faceNormal);
            fillTriangle(canvas, tri, fShader, {faceNormal.x, faceNormal.y, faceNormal.z, 0});
        }
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Rendering Time: " << elapsed.count() << " ms" << std::endl;
}

#endif //TOYRENDERER2_RENDERER_H