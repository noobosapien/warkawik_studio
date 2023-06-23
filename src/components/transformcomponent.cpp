#include "../headers/gamepch.h"

TransformComponent::TransformComponent(Actor *owner) : Component(owner)
{
    mTransform.position = glm::vec3(mOwner->getPosition(), 0.f);
    mTransform.scale = glm::vec3(mOwner->getScale());

    mTransform.rotation = Quat::angleAxis(mOwner->getRotation(), glm::vec3(mOwner->getForward(), 0.f));
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::updateInfo()
{
    mTransform.position = glm::vec3(mOwner->getPosition(), 0.f);
    mTransform.scale = glm::vec3(mOwner->getScale());

    mTransform.rotation = Quat::angleAxis(mOwner->getRotation(), glm::vec3(mOwner->getForward(), 0.f));
}

void TransformComponent::updateOwner()
{
    mOwner->setPosition(glm::vec2(mTransform.position.x, mTransform.position.y));
    mOwner->setScale(mTransform.scale.x);
    mOwner->setRotation(glm::degrees(Quat::getAngle(mTransform.rotation)));
}

void TransformComponent::setTransform(Transform transform)
{
    mTransform = transform;
    updateOwner();
}

void TransformComponent::changePosition(glm::vec3 position)
{
    mTransform.position = position;
    mOwner->setPosition(glm::vec2(position.x, position.y));
}

void TransformComponent::changeScale(glm::vec3 scale)
{
    mTransform.scale = scale;
    mOwner->setScale(scale.x);
}

void TransformComponent::changeRotation(Quat rotation)
{
    mTransform.rotation = rotation;
    mOwner->setRotation(glm::degrees(Quat::getAngle(mTransform.rotation)));
}

void TransformComponent::changeRotation(float rotation)
{
    mTransform.rotation = Quat::angleAxis(rotation, glm::vec3(mOwner->getForward(), 0.f));
    mOwner->setRotation(rotation);
}

Transform TransformComponent::combine(const Transform &a, const Transform &b)
{
    Transform out;

    out.scale = a.scale * b.scale;
    out.rotation = b.rotation * a.rotation;
    out.position = a.rotation * (a.scale * b.position);
    out.position = a.position + out.position;

    // placeholder
    out.scale = glm::vec3(0.2);

    std::cout << "Position: " << out.position.x << ", " << out.position.y << std::endl;
    std::cout << "Scale: " << out.scale.x << ", " << out.scale.y << std::endl;
    std::cout << "Rotation: " << Quat::getAngle(out.rotation) << std::endl;

    return out;
}

Transform TransformComponent::inverse(const Transform &t)
{
    Transform inv;

    inv.rotation = Quat::inverse(t.rotation);

    inv.scale.x = fabs(t.scale.x) < VEC3_EPSILON ? 0.f : 1.f / t.scale.x;
    inv.scale.y = fabs(t.scale.y) < VEC3_EPSILON ? 0.f : 1.f / t.scale.y;
    inv.scale.z = fabs(t.scale.z) < VEC3_EPSILON ? 0.f : 1.f / t.scale.z;

    glm::vec3 invTrans = t.position * -1.f;
    inv.position = inv.rotation * (inv.scale * invTrans); // might need to change the order

    return inv;
}

Transform TransformComponent::mix(const Transform &a, const Transform &b, float t)
{
    Quat bRot = b.rotation;

    if (Quat::dot(a.rotation, bRot) < 0.f)
    {
        bRot = -bRot;
    }

    return Transform{
        MathUtils::lerp(a.position, b.position, t),
        MathUtils::lerp(a.scale, b.scale, t),
        Quat::nlerp(a.rotation, bRot, t)};
}