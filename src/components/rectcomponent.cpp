#include "../headers/gamepch.h"

RectangleComponent::RectangleComponent(Actor *owner, glm::vec2 position, float rotation, glm::vec2 size) : Component(owner),
                                                                                                           mPosition(position),
                                                                                                           mRotation(rotation),
                                                                                                           mSize(size)
{
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::changePosition(const glm::vec2 &position)
{
    mPosition = position;
}

void RectangleComponent::changeRotation(float rotation)
{
    mRotation = rotation;
}

void RectangleComponent::changeSize(const glm::vec2 &size)
{
    mSize = size;
}

bool RectangleComponent::checkCollisionWithPoint(const glm::vec2 &point)
{
    // project point to top and bottom vectors and find if the distance is less than top and bottom vectors
}