#include "../transform.h"

Transform::Transform()
    : position(0.0f), rotation(0.0f, 0.0f, 0.0f, 1.0f), scale(1.0f), parent(nullptr) 
{}

mat4 Transform::GetLocalMatrix() const {
    mat4 translationMatrix = mat4::translation(position);
    mat4 rotationMatrix = rotation.toMat4();
    mat4 scaleMatrix = mat4::scale(scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}

quat Transform::GetGlobalRotation() const {
    quat globalRotation = rotation;
    Transform* currentParent = parent;

    while (currentParent) {
        globalRotation = currentParent->rotation * globalRotation;
        currentParent = currentParent->parent;
    }

    return globalRotation;
}

mat4 Transform::GetGlobalMatrix() const {
    mat4 globalMatrix = GetLocalMatrix();
    Transform* currentParent = parent;

    while (currentParent) {
        globalMatrix = currentParent->GetLocalMatrix() * globalMatrix;
        currentParent = currentParent->parent;
    }

    return globalMatrix;
}

vec3 Transform::GetGlobalScale() const {
    vec3 globalScale = scale;
    Transform* currentParent = parent;

    while (currentParent) {
        globalScale.x *= currentParent->scale.x;
        globalScale.y *= currentParent->scale.y;
        globalScale.z *= currentParent->scale.z;
        currentParent = currentParent->parent;
    }

    return globalScale;
}

vec3 Transform::GetGlobalPosition() const {
    vec3 globalPosition = position;
    Transform* currentParent = parent;

    while (currentParent) {
        globalPosition = currentParent->position + (currentParent->rotation * (currentParent->scale * globalPosition));
        currentParent = currentParent->parent;
    }

    return globalPosition;
}

void Transform::SetRotation(const vec3& axis, float angle) {
    rotation = quat::fromAxisAngle(axis, angle);
}

void Transform::SetRotationFromEuler(const vec3& eulerAngles) {
    float yaw = degrees_to_radians(eulerAngles.y);  // Yaw (rotation around y-axis)
    float pitch = degrees_to_radians(eulerAngles.x); // Pitch (rotation around x-axis)
    float roll = degrees_to_radians(eulerAngles.z);  // Roll (rotation around z-axis)

    float cy = cosf(yaw * 0.5f);  // cos(yaw / 2)
    float sy = sinf(yaw * 0.5f);  // sin(yaw / 2)
    float cp = cosf(pitch * 0.5f);  // cos(pitch / 2)
    float sp = sinf(pitch * 0.5f);  // sin(pitch / 2)
    float cr = cosf(roll * 0.5f);   // cos(roll / 2)
    float sr = sinf(roll * 0.5f);   // sin(roll / 2)

    rotation.x = cy * sp * cr + sy * cp * sr;
    rotation.y = sy * cp * cr - cy * sp * sr;
    rotation.z = cy * cp * sr - sy * sp * cr;
    rotation.w = cy * cp * cr + sy * sp * sr;
}

void Transform::Rotate(const vec3& axis, float angle) {
    quat incrementalRotation = quat::fromAxisAngle(axis, angle);
    rotation = (incrementalRotation * rotation).normalize();
}

vec3 Transform::forward() const {
    return GetGlobalRotation() * vec3(0.0f, 0.0f, -1.0f);
}

vec3 Transform::up() const {
    return GetGlobalRotation() * vec3(0.0f, 1.0f, 0.0f);
}

vec3 Transform::right() const {
    return GetGlobalRotation() * vec3(1.0f, 0.0f, 0.0f);
}

void Transform::SetParent(Transform* newParent) {
    parent = newParent;
}
