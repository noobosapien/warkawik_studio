#include "../headers/gamepch.h"

RectangleComponent::RectangleComponent(Actor *owner, glm::vec2 position, float rotation, glm::vec2 size) : Component(owner),
                                                                                                           mPosition(position),
                                                                                                           mRotation(rotation),
                                                                                                           mSize(size)
{

    mA = glm::vec2(0.f);
    mB = glm::vec2(0.f);
    mC = glm::vec2(0.f);
    mD = glm::vec2(0.f);

    mPlaneAB = glm::vec3(0.f);
    mPlaneBC = glm::vec3(0.f);
    mPlaneCD = glm::vec3(0.f);
    mPlaneAD = glm::vec3(0.f);

    init();
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::init()
{
}

void RectangleComponent::changePosition(const glm::vec2 &position)
{
    mPosition = position;
    recomputePlanes();
}

void RectangleComponent::changeRotation(float rotation)
{
    mRotation = rotation;
    recomputePlanes();
}

void RectangleComponent::changeSize(const glm::vec2 &size)
{
    mSize = size;
    recomputePlanes();
}

bool RectangleComponent::checkCollisionWithPoint(const glm::vec2 &point)
{
    bool val = false;

    return val;
}

void RectangleComponent::recomputePlanes()
{
    glm::vec2 pos = mOwner->getPosition();
    float size = mOwner->getScale();
    float rotation = mOwner->getRotation();

    glm::vec3 A = glm::vec3(pos.x - (size / 2), pos.y + (size / 2), 0.f);
    glm::vec3 B = glm::vec3(pos.x + (size / 2), pos.y + (size / 2), 0.f);
    glm::vec3 C = glm::vec3(pos.x + (size / 2), pos.y - (size / 2), 0.f);
    glm::vec3 D = glm::vec3(pos.x - (size / 2), pos.y - (size / 2), 0.f);

    float halfRot = rotation / 2;
    float sinRot = sin(halfRot);
    float cosRot = cos(halfRot);

    Quat rotQuat = Quat(0., 0., sinRot, cosRot); // axis of rotation is only Z
    Quat inverse = Quat::inverse(rotQuat);

    mA = rotQuat * A; // hope it's commutative
    mA = inverse * A;

    mB = rotQuat * B;
    mB = inverse * B;

    mC = rotQuat * C;
    mC = inverse * C;

    mD = rotQuat * D;
    mD = inverse * D;

    // mPlaneAB
}