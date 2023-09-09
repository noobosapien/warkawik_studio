#include "../headers/gamepch.h"

Part::Part(Game *game, unsigned int id) : Actor(game),
                                          mSelected(false),
                                          mId(id)
{
    mTransform = new TransformComponent(this);
    mTransform->changeRotation(Quat(1, 1, 1, 0.));

    new SelectComponent(this);
}

Part::~Part()
{
}