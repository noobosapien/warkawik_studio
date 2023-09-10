#include "../../headers/gamepch.h"

Button::Button(Game *game, unsigned int id) : Actor(game),
                                              mId(id),
                                              mVisible(true),
                                              mNormalSprite(nullptr),
                                              mHoveringSprite(nullptr),
                                              mClickedSprite(nullptr)
{
    mTransform = new TransformComponent(this);
    mTransform->changeRotation(Quat(1, 1, 1, 0.));
}

Button::~Button()
{
}