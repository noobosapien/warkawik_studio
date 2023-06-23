#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#define VEC3_EPSILON 0.000001f

namespace MathUtils
{
    float angle(const glm::vec3 &l, const glm::vec3 &r);

    glm::vec3 lerp(const glm::vec3 &s, const glm::vec3 &e, float t);
    glm::vec3 slerp(const glm::vec3 &s, const glm::vec3 &e, float t);

    glm::vec3 nlerp(const glm::vec3 &s, const glm::vec3 &e, float t);
}

#endif