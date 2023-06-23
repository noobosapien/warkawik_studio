#include "../headers/gamepch.h"

Part::Part(Game *game) : Actor(game)
{
    mTransform = new TransformComponent(this);
    mTransform->changeRotation(Quat(1, 1, 1, 0.5));
}

Part::~Part()
{
}