//
// Created by Sohal03 on 26. 3. 19..
//

#ifndef TOYRENDERER2_GEOMETRY_H
#define TOYRENDERER2_GEOMETRY_H
#include <cmath>
#include <initializer_list>
#include <span>
#include <cmath>

template <int R, int C>
struct Mat {
    float data[R * C]{};
    int rows{R}, cols{C};

    // 생성자 짬통
    Mat() {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (i == j) data[i * C + j] = 1.;
                else data[i * C + j] = 0.;
            }
        }
    }

    Mat(const Mat& m) {
        for (int i = 0; i < R * C; i++) {
            data[i] = m.data[i];
        }
    }

    float* operator[](int i) {
        return &data[i * C];
    }

    const float* operator[](int i) const {
        return &data[i * C];
    }

    void zero() {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                data[i * C + j] = 0.;
            }
        }
    }
};

struct Vec3 {
    float x = 0, y = 0, z = 0;

    // 생성자 짬통
    Vec3() = default;
    Vec3(const Vec3& v3) = default;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const std::initializer_list<float> list) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it != list.end()) x = *it++;
            if (it != list.end()) y = *it++;
            if (it != list.end()) z = *it++;
        }
    }
    Vec3& operator=(const Vec3& v) = default;

    // 연산자 오버로딩

    // 벡터덧셈
    Vec3 operator+(Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3& operator+=(Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 벡터뺼셈
    Vec3 operator-(Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec3& operator-=(Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 스칼라곱셈
    Vec3 operator*(const float s) const { return {x * s, y * s, z * s}; }
    Vec3& operator*=(const float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // 스칼라나눗셈
    Vec3 operator/(const float s) const { return {x / s, y / s, z / s}; }
    Vec3& operator/=(const float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // 내적
    [[nodiscard]] float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    // 외적
    [[nodiscard]] Vec3 cross(const Vec3& v) const { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }

    //비교
    bool operator==(const Vec3& v) const = default;
};

struct Vec4 {
    float x = 0, y = 0, z = 0, w = 0;

    // 생성자 짬통
    Vec4() = default;
    Vec4(const Vec4& v4) = default;
    Vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    Vec4(const std::initializer_list<float> list) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it != list.end()) x = *it++;
            if (it != list.end()) y = *it++;
            if (it != list.end()) z = *it++;
            if (it != list.end()) w = *it++;
        }
    }
    Vec4& operator=(const Vec4& v) = default;

    // 연산자 오버로딩

    // 벡터덧셈
    Vec4 operator+(Vec4& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec4 operator+(const Vec4& v) const  { return {x + v.x, y + v.y, z + v.z}; };
    Vec4& operator+=(const Vec4& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    // 벡터뺼셈
    Vec4 operator-(Vec4& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec4 operator-(const Vec4& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec4& operator-=(const Vec4& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    // 스칼라곱셈
    Vec4 operator*(const float s) const { return {x * s, y * s, z * s}; }
    Vec4& operator*=(const float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // 스칼라나눗셈
    Vec4 operator/(const float s) const { return {x / s, y / s, z / s}; }
    Vec4& operator/=(const float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // 내적
    [[nodiscard]] float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    bool operator==(const Vec4 & vec4) const = default;

    int operator*(int _cpp_par_) const;
};

struct Vec2 {
    float x, y;
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    float& operator[](int i) { return (&x)[i]; }

    bool operator==(const Vec2 & vec2) const = default;

    Vec2 operator-(const float& rhs) const {
        return {x - rhs, y - rhs};
    }
};

inline Vec4 operator*(const Mat<4, 4>& m, const Vec4& v) {
    float res[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        res[i] = m[i][0] * v.x + m[i][1] * v.y + m[i][2] * v.z + m[i][3] * v.w;
    }
    return {res[0], res[1], res[2], res[3]};
}

using Mat44 = Mat<4, 4>;

inline Mat44 operator*(const Mat44& m, const Mat44& v) {
    Mat44 res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float temp = 0;
            for (int k = 0; k < 4; k++) {
                temp += m[i][k] * v[k][j];
            }
            res[i][j] = temp;
        }
    }
    return res;
}

inline Mat44& operator*=(Mat44& m, Mat44& v) {
    m = m * v;
    return m;
}

static Vec3 normalize(const Vec3 &v) {
    const float norm = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (norm < 1e-6) ? v : Vec3{v.x/norm, v.y/norm, v.z/norm};
}

static Vec4 normalize(const Vec4 &v) {
    const float norm = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    return (norm < 1e-6) ? v : Vec4{v.x/norm, v.y/norm, v.z/norm, v.w/norm};
}

static Vec3 barycentric(const Vec2 p, const std::span<const Vec2, 3> pts) {
    const Vec3 vx = {pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - p.x};
    const Vec3 vy = {pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - p.y};
    const Vec3 u = vx.cross(vy);
    if (std::abs(u.z) < 1e-2) return {-1, 1, 1};

    float u_val = u.x / u.z;
    float v_val = u.y / u.z;

    return {1.f - (u_val + v_val), u_val, v_val};
}
static Mat44 perspective(const float fovDeg, const float aspect, const float near, const float far) {
    const float fovRad = fovDeg * (3.14159265f / 180.0f);
    const float t = std::tan(fovRad / 2.0f);

    Mat44 m;
    m.zero();

    m[0][0] = 1.0f / (aspect * t);
    m[1][1] = 1.0f / t;
    m[2][2] = -(far + near) / (far - near);
    m[2][3] = -(2.0f * far * near) / (far - near);
    m[3][2] = -1.0f;

    return m;
}

static void translate(Mat44& model, const float x, const float y, const float z) {
    model[0][3] += x;
    model[1][3] += y;
    model[2][3] += z;
}

static void rotate(Mat44& model, const float x, float y, float z) {
    auto rotX = Mat44();
    const float sx = std::sin(x);
    const float cx = std::cos(x);
    rotX[1][1] = cx;
    rotX[1][2] = -sx;
    rotX[2][1] = sx;
    rotX[2][2] = cx;

    auto rotY = Mat44();
    const float sy = std::sin(y);
    const float cy = std::cos(y);
    rotY[0][0] = cy;
    rotY[0][2] = sy;
    rotY[2][0] = -sy;
    rotY[2][2] = cy;

    auto rotZ = Mat44();
    const float sz = std::sin(z);
    const float cz = std::cos(z);
    rotZ[0][0] = cz;
    rotZ[0][1] = -sz;
    rotZ[1][0] = sz;
    rotZ[1][1] = cz;

    model *= rotZ *= rotY *= rotX;
}

#endif //TOYRENDERER2_GEOMETRY_H