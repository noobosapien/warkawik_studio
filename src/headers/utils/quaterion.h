#ifndef QUATERION_H
#define QUATERION_H

#define QUAT_EPSILON 0.000001f

struct quat
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };

        struct
        {
            glm::vec3 vector;
            float scalar;
        };

        float v[4];
    } UQuaterion;

    inline quat()
    {
        UQuaterion.x = 0.f;
        UQuaterion.y = 0.f;
        UQuaterion.z = 0.f;
        UQuaterion.w = 0.f;
    }

    inline quat(float _x, float _y, float _z, float _w)
    {
        UQuaterion.x = _x;
        UQuaterion.y = _y;
        UQuaterion.z = _z;
        UQuaterion.w = _w;
    }
};

quat operator+(const quat &a, const quat &b);
quat operator-(const quat &a, const quat &b);
quat operator*(const quat &a, float b);
quat operator-(const quat &q);

quat operator*(const quat &Q1, const quat &Q2);
glm::vec3 operator*(const quat &Q1, const glm::vec3 &v);

bool operator==(const quat &left, const quat &right);
bool operator!=(const quat &left, const quat &right);
quat operator^(const quat &quat, float f);

namespace Quaterion
{
    quat angleAxis(float angle, const glm::vec3 &axis);
    quat fromTo(const glm::vec3 &from, const glm::vec3 &to);

    glm::vec3 getAxis(const quat &q);
    float getAngle(const quat &q);

    bool sameOrientation(const quat &left, const quat &right);

    float dot(const quat &a, const quat &b);
    float lenSq(const quat &q);
    float len(const quat &q);

    void normalize(quat &q);

    quat normalized(const quat &q);
    quat conjugate(const quat &q);
    quat inverser(const quat &q);

    quat mix(const quat &from, const quat &to, float t);
    quat nlerp(const quat &from, const quat &to, float t);

    quat slerp(const quat &start, const quat &end, float t);
    quat lookRotation(const glm::vec3 &direction, const glm::vec3 &up);

    glm::mat4 quatToMat4(const quat &q);
    quat mat4ToQuat(const glm::mat4 &m);
}

#endif