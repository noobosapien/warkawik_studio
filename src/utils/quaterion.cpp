#include "../headers/gamepch.h"

namespace Quaterion
{

    quat angleAxis(float angle, const glm::vec3 &axis)
    {
        glm::vec3 norm = glm::normalize(axis);
        float s = sinf(angle * 0.5f);

        return quat(
            norm.x * s,
            norm.y * s,
            norm.z * s,
            cosf(angle * 0.5f));
    }

    quat fromTo(const glm::vec3 &from, const glm::vec3 &to)
    {
        glm::vec3 f = glm::normalize(from);
        glm::vec3 t = glm::normalize(to);

        if (f == t)
        {
            return quat();
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
            return quat(axis.x, axis.y, axis.z, 0);
        }

        glm::vec3 half = glm::normalize(f + t);
        glm::vec3 axis = glm::cross(f, half);

        return quat(
            axis.x, axis.y, axis.z, dot(f, half));
    }

    glm::vec3 getAxis(const quat &q)
    {
        return glm::normalize(glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z));
    }

    float getAngle(const quat &q)
    {
        return 2.f * acosf(q.UQuaterion.w);
    }

    bool sameOrientation(const quat &left, const quat &right)
    {
        return (
            fabsf(left.UQuaterion.x - right.UQuaterion.x) <= QUAT_EPSILON && fabsf(left.UQuaterion.y - right.UQuaterion.y) <= QUAT_EPSILON && fabsf(left.UQuaterion.z - right.UQuaterion.z) <= QUAT_EPSILON && fabsf(left.UQuaterion.w - right.UQuaterion.w) <= QUAT_EPSILON || fabsf(left.UQuaterion.x + right.UQuaterion.x) <= QUAT_EPSILON && fabsf(left.UQuaterion.y + right.UQuaterion.y) <= QUAT_EPSILON && fabsf(left.UQuaterion.z + right.UQuaterion.z) <= QUAT_EPSILON && fabsf(left.UQuaterion.w + right.UQuaterion.w) <= QUAT_EPSILON);
    }

    float dot(const quat &a, const quat &b)
    {
        return a.UQuaterion.x * b.UQuaterion.x + a.UQuaterion.y * b.UQuaterion.y + a.UQuaterion.z * b.UQuaterion.z + a.UQuaterion.w * b.UQuaterion.w;
    }

    float lenSq(const quat &q)
    {
        return q.UQuaterion.x * q.UQuaterion.x + q.UQuaterion.y * q.UQuaterion.y + q.UQuaterion.z * q.UQuaterion.z + q.UQuaterion.w * q.UQuaterion.w;
    }

    float len(const quat &q)
    {
        float lenSq = q.UQuaterion.x * q.UQuaterion.x + q.UQuaterion.y * q.UQuaterion.y + q.UQuaterion.z * q.UQuaterion.z + q.UQuaterion.w * q.UQuaterion.w;

        if (lenSq < QUAT_EPSILON)
        {
            return 0.f;
        }

        return sqrtf(lenSq);
    }

    void normalize(quat &q)
    {
        float lenSq = q.UQuaterion.x * q.UQuaterion.x + q.UQuaterion.y * q.UQuaterion.y + q.UQuaterion.z * q.UQuaterion.z + q.UQuaterion.w * q.UQuaterion.w;

        if (lenSq < QUAT_EPSILON)
        {
            return;
        }

        float i_len = 1.f / sqrtf(lenSq);

        q.UQuaterion.x *= i_len;
        q.UQuaterion.y *= i_len;
        q.UQuaterion.z *= i_len;
        q.UQuaterion.w *= i_len;
    }

    quat normalized(const quat &q)
    {
        float lenSq = q.UQuaterion.x * q.UQuaterion.x + q.UQuaterion.y * q.UQuaterion.y + q.UQuaterion.z * q.UQuaterion.z + q.UQuaterion.w * q.UQuaterion.w;

        if (lenSq < QUAT_EPSILON)
        {
            return quat();
        }

        float i_len = 1.f / sqrtf(lenSq);

        return quat(
            q.UQuaterion.x * i_len,
            q.UQuaterion.y * i_len,
            q.UQuaterion.z * i_len,
            q.UQuaterion.w * i_len);
    }

    quat conjugate(const quat &q)
    {
        return quat(
            -q.UQuaterion.x, -q.UQuaterion.y, -q.UQuaterion.z, q.UQuaterion.w);
    }

    quat inverse(const quat &q)
    {
        float lenSq = q.UQuaterion.x * q.UQuaterion.x + q.UQuaterion.y * q.UQuaterion.y + q.UQuaterion.z * q.UQuaterion.z + q.UQuaterion.w * q.UQuaterion.w;

        if (lenSq < QUAT_EPSILON)
        {
            return quat();
        }

        float recip = 1.f / lenSq;

        return quat(
            -q.UQuaterion.x * recip,
            -q.UQuaterion.y * recip,
            -q.UQuaterion.z * recip,
            q.UQuaterion.w * recip);
    }

    quat mix(const quat &from, const quat &to, float t)
    {
        return from * (1.f - t) + to * t;
    }

    quat nlerp(const quat &from, const quat &to, float t)
    {
        return normalized(from + (to - from) * t);
    }

    quat slerp(const quat &start, const quat &end, float t)
    {
        if (fabsf(dot(start, end)) > 1.f - QUAT_EPSILON)
        {
            return nlerp(start, end, t);
        }

        return normalized(((inverse(start) * end) ^ t) * start);
    }

    quat lookRotation(const glm::vec3 &direction, const glm::vec3 &up)
    {
        glm::vec3 f = glm::normalize(direction);
        glm::vec3 u = glm::normalize(up);
        glm::vec3 r = glm::cross(u, f);
        u = glm::cross(f, r);

        quat f2d = fromTo(glm::vec3(0, 0, 1), f);

        glm::vec3 objectUp = f2d * glm::vec3(0, 1, 0);

        quat u2u = fromTo(objectUp, u);

        quat result = f2d * u2u;

        return normalized(result);
    }

    glm::mat4 quatToMat4(const quat &q)
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

    quat mat4ToQuat(const glm::mat4 &m)
    {
        // glm::vec3 up = glm::normalize(glm::vec3(m.up.x, m.up.y, m.up.z));
        // glm::vec3 forward = glm::normalize(glm::vec3(m.forward.x, m.forward.y, m.forward.z));
        // glm::vec3 right = glm::cross(up, forward);
        // up = glm::cross(forward, right);

        // return lookRotation(forward, up);
        return quat();
    }
}

quat operator+(const quat &a, const quat &b)
{
    return quat(a.UQuaterion.x + b.UQuaterion.x, a.UQuaterion.y + b.UQuaterion.y, a.UQuaterion.z + b.UQuaterion.z, a.UQuaterion.w + b.UQuaterion.w);
}

quat operator-(const quat &a, const quat &b)
{
    return quat(a.UQuaterion.x - b.UQuaterion.x, a.UQuaterion.y - b.UQuaterion.y, a.UQuaterion.z - b.UQuaterion.z, a.UQuaterion.w - b.UQuaterion.w);
}

quat operator*(const quat &a, float b)
{
    return quat(a.UQuaterion.x * b, a.UQuaterion.y * b, a.UQuaterion.z * b, a.UQuaterion.w * b);
}

quat operator-(const quat &q)
{
    return quat(-q.UQuaterion.x, -q.UQuaterion.y, -q.UQuaterion.z, -q.UQuaterion.w);
}

bool operator==(const quat &left, const quat &right)
{
    return (
        fabsf(left.UQuaterion.x - right.UQuaterion.x) <= QUAT_EPSILON && fabsf(left.UQuaterion.y - right.UQuaterion.y) <= QUAT_EPSILON && fabsf(left.UQuaterion.z - right.UQuaterion.z) <= QUAT_EPSILON);
}

bool operator!=(const quat &a, const quat &b)
{
    return !(a == b);
}

quat operator*(const quat &Q1, const quat &Q2)
{
    return quat(
        Q2.UQuaterion.x * Q1.UQuaterion.w + Q2.UQuaterion.y * Q1.UQuaterion.z - Q2.UQuaterion.z * Q1.UQuaterion.y + Q2.UQuaterion.w * Q1.UQuaterion.x,
        -Q2.UQuaterion.x * Q1.UQuaterion.z + Q2.UQuaterion.y * Q1.UQuaterion.w + Q2.UQuaterion.z * Q1.UQuaterion.x + Q2.UQuaterion.w * Q1.UQuaterion.y,
        Q2.UQuaterion.x * Q1.UQuaterion.y - Q2.UQuaterion.y * Q1.UQuaterion.x + Q2.UQuaterion.z * Q1.UQuaterion.w + Q2.UQuaterion.w * Q1.UQuaterion.z,
        -Q2.UQuaterion.x * Q1.UQuaterion.x - Q2.UQuaterion.y * Q1.UQuaterion.y - Q2.UQuaterion.z * Q1.UQuaterion.z + Q2.UQuaterion.w * Q1.UQuaterion.w);
}

glm::vec3 operator*(const quat &q, const glm::vec3 &v)
{
    return glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z) * 2.f * glm::dot(glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z), v) + v * (q.UQuaterion.w * q.UQuaterion.w - glm::dot(glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z), glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z))) + glm::cross(glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z), v) * 2.f * q.UQuaterion.w;
}

quat operator^(const quat &q, float f)
{
    float angle = 2.f * acosf(q.UQuaterion.w);

    glm::vec3 axis = glm::normalize(glm::vec3(q.UQuaterion.x, q.UQuaterion.y, q.UQuaterion.z));

    float halfCos = cosf(f * angle * 0.5f);
    float halfSin = sinf(f * angle * 0.5f);

    return quat(
        axis.x * halfSin, axis.y * halfSin, axis.z * halfSin, halfCos);
}
