#include "../headers/gamepch.h"

Part::Part(Game *game) : Actor(game), mSelected(false)
{
    mTransform = new TransformComponent(this);
    mTransform->changeRotation(Quat(1, 1, 1, 0.));

    new SelectComponent(this);
}

Part::~Part()
{
}