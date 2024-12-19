#pragma once

#include <cmath>
#include <cstring>

#define PI 3.14159265358979323846

// -------------------- VECTOR 2 (vec2) --------------------
struct vec2 {
    float x, y;

    vec2() : x(0), y(0) {}
    vec2(float v) : x(v), y(v) {}
    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator+(const vec2& other) const { return {x + other.x, y + other.y}; }
    vec2& operator+=(const vec2& other) { x += other.x; y += other.y; return *this; }

    vec2 operator-(const vec2& other) const { return {x - other.x, y - other.y}; }
    vec2& operator-=(const vec2& other) { x -= other.x; y -= other.y; return *this; }

    vec2 operator*(const vec2& other) const { return {x * other.x, y * other.y}; }
    vec2& operator*=(const vec2& other) { x *= other.x; y *= other.y; return *this; }

    vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
    vec2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

    float dot(const vec2& other) const { return x * other.x + y * other.y; }
    float cross(const vec2& other) const { return x * other.y - y * other.y; }

    float length() const { return std::sqrt(x * x + y * y);}

    vec2 normalize() const {
        float len = length();
        return len > 0 ? (*this * (1.0f / len)) : vec2();
    }

    vec2 lerp(const vec2& to, float t) const { return*this + (to - *this) * t; }
};

// -------------------- VECTOR 3 (vec3) --------------------
struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}
    vec3(float v) : x(v), y(v), z(v) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& other) const { return {x + other.x, y + other.y, z + other.z}; }
    vec3& operator+=(const vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }

    vec3 operator-(const vec3& other) const { return {x - other.x, y - other.y, z - other.z}; }
    vec3& operator-=(const vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }

    vec3 operator*(const vec3& other) const { return {x * other.x, y * other.y, z * other.z}; }
    vec3& operator*=(const vec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }

    vec3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    vec3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }


    float dot(const vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    vec3 cross(const vec3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    float length() const { return std::sqrt(x * x + y * y + z * z); }

    vec3 normalize() const {
        float len = length();
        return len > 0 ? (*this * (1.0f / len)) : vec3();
    }

    vec3 lerp(const vec3& to, float t) const { return *this + (to - *this) * t; }
};

// -------------------- MATRIX 4x4 (mat4) --------------------
struct mat4 {
    float elements[16]; // Row-major order

    mat4() { memset(elements, 0, sizeof(elements)); for (int i = 0; i < 4; i++) elements[i + i * 4] = 1.0f; }

    float& operator()(int row, int col) { return elements[col * 4 + row]; }
    const float& operator()(int row, int col) const { return elements[col * 4 + row]; }

    mat4 operator*(const mat4& other) const {
        mat4 result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result(row, col) = 0.0f;
                for (int k = 0; k < 4; k++) {
                    result(row, col) += (*this)(row, k) * other(k, col);
                }
            }
        }
        return result;
    }

    static mat4 translation(const vec3& t) {
        mat4 result;
        result(0, 3) = t.x;
        result(1, 3) = t.y;
        result(2, 3) = t.z;
        return result;
    }

    static mat4 scale(const vec3& s) {
        mat4 result;
        result(0, 0) = s.x;
        result(1, 1) = s.y;
        result(2, 2) = s.z;
        return result;
    }

    static mat4 rotateX(float angle) {
        mat4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result(1, 1) = c; result(1, 2) = -s;
        result(2, 1) = s; result(2, 2) = c;
        return result;
    }

    static mat4 rotateY(float angle) {
        mat4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result(0, 0) = c; result(0, 2) = s;
        result(2, 0) = -s; result(2, 2) = c;
        return result;
    }

    static mat4 rotateZ(float angle) {
        mat4 result;
        float c = std::cos(angle);
        float s = std::sin(angle);
        result(0, 0) = c; result(0, 1) = -s;
        result(1, 0) = s; result(1, 1) = c;
        return result;
    }

    static mat4 perspective(float fov, float aspect, float near, float far) {
        mat4 result;
        float tanHalfFOV = std::tan(fov / 2.0f);
        result(0, 0) = 1.0f / (aspect * tanHalfFOV);
        result(1, 1) = 1.0f / tanHalfFOV;
        result(2, 2) = -(far + near) / (far - near);
        result(2, 3) = -(2.0f * far * near) / (far - near);
        result(3, 2) = -1.0f;
        result(3, 3) = 0.0f;
        return result;
    }

    static mat4 orthographic(float left, float right, float bottom, float top, float near, float far) {
        mat4 result;
        result(0, 0) = 2.0f / (right - left);
        result(1, 1) = 2.0f / (top - bottom);
        result(2, 2) = -2.0f / (far - near);
        result(0, 3) = -(right + left) / (right - left);
        result(1, 3) = -(top + bottom) / (top - bottom);
        result(2, 3) = -(far + near) / (far - near);
        return result;
    }

    static mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
        vec3 f = (center - eye).normalize();
        vec3 r = f.cross(up).normalize();
        vec3 u = r.cross(f);

        mat4 result;
        result(0, 0) = r.x; result(0, 1) = r.y; result(0, 2) = r.z;
        result(1, 0) = u.x; result(1, 1) = u.y; result(1, 2) = u.z;
        result(2, 0) = -f.x; result(2, 1) = -f.y; result(2, 2) = -f.z;
        result(0, 3) = -r.dot(eye);
        result(1, 3) = -u.dot(eye);
        result(2, 3) = f.dot(eye);
        return result;
    }
};

// -------------------- QUATERNION (quat) --------------------
struct quat {
    float x, y, z, w;

    quat() : x(0), y(0), z(0), w(1) {}
    quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    quat operator*(const quat& other) const {
        return {
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z
        };
    }

    quat normalize() const {
        float len = std::sqrt(x * x + y * y + z * z + w * w);
        return len > 0 ? quat(x / len, y / len, z / len, w / len) : quat();
    }

    mat4 toMat4() const {
        mat4 result;
        float xx = x * x, yy = y * y, zz = z * z;
        float xy = x * y, xz = x * z, yz = y * z;
        float wx = w * x, wy = w * y, wz = w * z;

        result(0, 0) = 1.0f - 2.0f * (yy + zz);
        result(0, 1) = 2.0f * (xy - wz);
        result(0, 2) = 2.0f * (xz + wy);

        result(1, 0) = 2.0f * (xy + wz);
        result(1, 1) = 1.0f - 2.0f * (xx + zz);
        result(1, 2) = 2.0f * (yz - wx);

        result(2, 0) = 2.0f * (xz - wy);
        result(2, 1) = 2.0f * (yz + wx);
        result(2, 2) = 1.0f - 2.0f * (xx + yy);

        return result;
    }

    static quat fromAxisAngle(const vec3& axis, float angle) {
        float halfAngle = angle * 0.5f;
        float s = std::sin(halfAngle);
        return quat(axis.x * s, axis.y * s, axis.z * s, std::cos(halfAngle));
    }
};

inline vec3 operator*(const mat4& matrix, const vec3& vector) {
    float x = matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z + matrix(0, 3);
    float y = matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z + matrix(1, 3);
    float z = matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z + matrix(2, 3);
    float w = matrix(3, 0) * vector.x + matrix(3, 1) * vector.y + matrix(3, 2) * vector.z + matrix(3, 3);

    if (w != 0.0f && w != 1.0f) {
        return vec3(x / w, y / w, z / w);
    }

    return vec3(x, y, z);
}

inline vec3 operator*(const quat& q, const vec3& v) {
    vec3 qVec(q.x, q.y, q.z);
    vec3 uv = qVec.cross(v);
    vec3 uuv = qVec.cross(uv);
    uv *= (2.0f * q.w);
    uuv *= 2.0f;
    return v + uv + uuv;
}

inline float degrees_to_radians(float degrees) {
    return degrees * PI / 180.0;
}

inline float radian_to_degrees(float radians) {
    return radians * 180.0 / PI;
}

inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

inline float clamp(float min, float max, float val)
{
    if(val < min)
        return min;
    else if(val > max)
        return max;
    else 
        return val;
}