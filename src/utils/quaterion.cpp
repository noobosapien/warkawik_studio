#include "../headers/gamepch.h"

// namespace Quaterion
// {

Quat Quat::angleAxis(float angle, const glm::vec3 &axis)
{
    glm::vec3 norm = glm::normalize(axis);
    float s = sinf(angle * 0.5f);

    return Quat(
        norm.x * s,
        norm.y * s,
        norm.z * s,
        cosf(angle * 0.5f));
}

Quat Quat::fromTo(const glm::vec3 &from, const glm::vec3 &to)
{
    glm::vec3 f = glm::normalize(from);
    glm::vec3 t = glm::normalize(to);

    if (f == t)
    {
        return Quat();
    }

    else if (f == t * -1.0f)
    {
        glm::vec3 ortho = glm::vec3(1, 0, 0);

        if (fabsf(f.y) < fabsf(f.x))
        {
            ortho = glm::vec3(0, 1, 0);
        }

        if (fabsf(f.z) < fabs(f.y) && fabs(f.z) < fabsf(f.x))
        {
            ortho = glm::vec3(0, 0, 1);
        }

        glm::vec3 axis = glm::normalize(glm::cross(f, ortho));
        return Quat(axis.x, axis.y, axis.z, 0);
    }

    glm::vec3 half = glm::normalize(f + t);
    glm::vec3 axis = glm::cross(f, half);

    return Quat(
        axis.x, axis.y, axis.z, glm::dot(f, half));
}

glm::vec3 Quat::getAxis(const Quat &q)
{
    return glm::normalize(glm::vec3(q.x, q.y, q.z));
}

float Quat::getAngle(const Quat &q)
{
    return 2.f * acosf(q.w);
}

bool Quat::sameOrientation(const Quat &left, const Quat &right)
{
    return (
        fabsf(left.x - right.x) <= QUAT_EPSILON && fabsf(left.y - right.y) <= QUAT_EPSILON && fabsf(left.z - right.z) <= QUAT_EPSILON && fabsf(left.w - right.w) <= QUAT_EPSILON || fabsf(left.x + right.x) <= QUAT_EPSILON && fabsf(left.y + right.y) <= QUAT_EPSILON && fabsf(left.z + right.z) <= QUAT_EPSILON && fabsf(left.w + right.w) <= QUAT_EPSILON);
}

float Quat::dot(const Quat &a, const Quat &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float Quat::lenSq(const Quat &q)
{
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

float Quat::len(const Quat &q)
{
    float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

    if (lenSq < QUAT_EPSILON)
    {
        return 0.f;
    }

    return sqrtf(lenSq);
}

void Quat::normalize(Quat &q)
{
    float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

    if (lenSq < QUAT_EPSILON)
    {
        return;
    }

    float i_len = 1.f / sqrtf(lenSq);

    q.x *= i_len;
    q.y *= i_len;
    q.z *= i_len;
    q.w *= i_len;
}

Quat Quat::normalized(const Quat &q)
{
    float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

    if (lenSq < QUAT_EPSILON)
    {
        return Quat();
    }

    float i_len = 1.f / sqrtf(lenSq);

    return Quat(
        q.x * i_len,
        q.y * i_len,
        q.z * i_len,
        q.w * i_len);
}

Quat Quat::conjugate(const Quat &q)
{
    return Quat(
        -q.x, -q.y, -q.z, q.w);
}

Quat Quat::inverse(const Quat &q)
{
    float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

    if (lenSq < QUAT_EPSILON)
    {
        return Quat();
    }

    float recip = 1.f / lenSq;

    return Quat(
        -q.x * recip,
        -q.y * recip,
        -q.z * recip,
        q.w * recip);
}

Quat Quat::mix(const Quat &from, const Quat &to, float t)
{
    return from * (1.f - t) + to * t;
}

Quat Quat::nlerp(const Quat &from, const Quat &to, float t)
{
    return normalized(from + (to - from) * t);
}

Quat Quat::slerp(const Quat &start, const Quat &end, float t)
{
    if (fabsf(dot(start, end)) > 1.f - QUAT_EPSILON)
    {
        return nlerp(start, end, t);
    }

    return normalized(((inverse(start) * end) ^ t) * start);
}

Quat Quat::lookRotation(const glm::vec3 &direction, const glm::vec3 &up)
{
    glm::vec3 f = glm::normalize(direction);
    glm::vec3 u = glm::normalize(up);
    glm::vec3 r = glm::cross(u, f);
    u = glm::cross(f, r);

    Quat f2d = fromTo(glm::vec3(0, 0, 1), f);

    glm::vec3 objectUp = f2d * glm::vec3(0, 1, 0);

    Quat u2u = fromTo(objectUp, u);

    Quat result = f2d * u2u;

    return normalized(result);
}

glm::mat4 Quat::quatToMat4(const Quat &q)
{
    glm::vec3 r = q * glm::vec3(1, 0, 0);
    glm::vec3 u = q * glm::vec3(0, 1, 0);
    glm::vec3 f = q * glm::vec3(0, 0, 1);

    return glm::mat4(
        r.x, r.y, r.z, 0,
        u.x, u.y, u.z, 0,
        f.x, f.y, f.z, 0,
        0, 0, 0, 1); // might need col-major
}

Quat Quat::mat4ToQuat(const glm::mat4 &m)
{
    // glm::vec3 up = glm::normalize(glm::vec3(m.up.x, m.up.y, m.up.z));
    // glm::vec3 forward = glm::normalize(glm::vec3(m.forward.x, m.forward.y, m.forward.z));
    // glm::vec3 right = glm::cross(up, forward);
    // up = glm::cross(forward, right);

    // return lookRotation(forward, up);
    return Quat();
}
// }

Quat operator+(const Quat &a, const Quat &b)
{
    return Quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Quat operator-(const Quat &a, const Quat &b)
{
    return Quat(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Quat operator*(const Quat &a, float b)
{
    return Quat(a.x * b, a.y * b, a.z * b, a.w * b);
}

Quat operator-(const Quat &q)
{
    return Quat(-q.x, -q.y, -q.z, -q.w);
}

bool operator==(const Quat &left, const Quat &right)
{
    return (
        fabsf(left.x - right.x) <= QUAT_EPSILON && fabsf(left.y - right.y) <= QUAT_EPSILON && fabsf(left.z - right.z) <= QUAT_EPSILON);
}

bool operator!=(const Quat &a, const Quat &b)
{
    return !(a == b);
}

Quat operator*(const Quat &Q1, const Quat &Q2)
{
    return Quat(
        Q2.x * Q1.w + Q2.y * Q1.z - Q2.z * Q1.y + Q2.w * Q1.x,
        -Q2.x * Q1.z + Q2.y * Q1.w + Q2.z * Q1.x + Q2.w * Q1.y,
        Q2.x * Q1.y - Q2.y * Q1.x + Q2.z * Q1.w + Q2.w * Q1.z,
        -Q2.x * Q1.x - Q2.y * Q1.y - Q2.z * Q1.z + Q2.w * Q1.w);
}

glm::vec3 operator*(const Quat &q, const glm::vec3 &v)
{
    return glm::vec3(q.x, q.y, q.z) * 2.f * glm::dot(glm::vec3(q.x, q.y, q.z), v) + v * (q.w * q.w - glm::dot(glm::vec3(q.x, q.y, q.z), glm::vec3(q.x, q.y, q.z))) + glm::cross(glm::vec3(q.x, q.y, q.z), v) * 2.f * q.w;
}

Quat operator^(const Quat &q, float f)
{
    float angle = 2.f * acosf(q.w);

    glm::vec3 axis = glm::normalize(glm::vec3(q.x, q.y, q.z));

    float halfCos = cosf(f * angle * 0.5f);
    float halfSin = sinf(f * angle * 0.5f);

    return Quat(
        axis.x * halfSin, axis.y * halfSin, axis.z * halfSin, halfCos);
}
