#include <emscripten.h>
#include <string>
#include "Render/include/Canvas.h"
#include "Render/include/Renderer.h"
#include "Render/include/VertexShader.h"
#include "Render/include/data/Mesh.h"
#include "Render/include/library/Geometry.h"
#include "Render/include/Fragment/PhongShader.h"
#include "Render/include/Fragment/BlinnPhongShader.h"
#include "Render/include/Fragment/FlatShader.h"

extern "C" {
    Vec3 rot;
    Vec3 mmov;
    Vec3 vmov;
    Vec3 light_pos;
    Mesh model;
    Canvas* canvas;
    int w;
    int h;

    EMSCRIPTEN_KEEPALIVE
    void init_canvas(const int width, const int height) {
        delete canvas;
        canvas = new Canvas(width, height);
        w = width;
        h = height;
    }

    EMSCRIPTEN_KEEPALIVE
    void set_rotation(float x, float y, float z) {
        rot = {x, y, z};
    }

    EMSCRIPTEN_KEEPALIVE
    void set_model_translation(float x, float y, float z) {
        mmov = {x, y, z};
    }

    EMSCRIPTEN_KEEPALIVE
    void set_view_translation(float x, float y, float z) {
        vmov = {x, y, z};
    }

    EMSCRIPTEN_KEEPALIVE
    void load_obj(const char* path) {
        printf("Loading: %s\n", path);
        model.loadObj(path);
    }

    EMSCRIPTEN_KEEPALIVE
    void set_light_position(float x, float y, float z) {
        light_pos = {x, y, z};
    }

    EMSCRIPTEN_KEEPALIVE
    uint8_t* render(const int shaderNum) {
        const Mat44 projectionMat =
        perspective(60.0f, static_cast<float>(w)/static_cast<float>(h), 0.1f, 1000.0f);
        Material mtl;
        mtl.loadMtl("place holder");
        Mat44 modelMat;
        translate(modelMat, mmov.x, mmov.y, mmov.z);
        rotate(modelMat, rot.x, rot.y, rot.z);
        Mat44 viewMat;
        translate(viewMat, vmov.x, vmov.y, vmov.z);
        const VertexShader vShader(modelMat, viewMat, projectionMat);
        switch (shaderNum) {
            case 1: // flat shader
                DrawModel<FlatShader>(*canvas, model, mtl, vShader, light_pos);
                break;
            case 2: // Phong shader
                DrawModel<PhongShader>(*canvas, model, mtl, vShader, light_pos);
                break;
            case 3: // Blinn-Phong shader
                DrawModel<BlinnPhongShader>(*canvas, model, mtl, vShader, light_pos);
                break;
            default:
                DrawModel<BlinnPhongShader>(*canvas, model, mtl, vShader, light_pos);
                break;
        }
        return canvas->getRGBABuffer();
    }
}