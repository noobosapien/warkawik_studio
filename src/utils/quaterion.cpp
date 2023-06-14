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

}
