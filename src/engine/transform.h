#pragma once

#include "vmath.h"

class Transform {
public:
    vec3 position;
    quat rotation;
    vec3 scale;
    Transform* parent;

    Transform();

    mat4 GetLocalMatrix() const;

    mat4 GetGlobalMatrix() const;

    quat GetGlobalRotation() const;

    vec3 GetGlobalScale() const;

    void SetRotation(const vec3& axis, float angle);
	void SetRotationFromEuler(const vec3& eulerAngles);

    void Rotate(const vec3& axis, float angle);

    vec3 forward() const;
    vec3 up() const;
    vec3 right() const;

    void SetParent(Transform* newParent);

    vec3 GetGlobalPosition() const;
};
