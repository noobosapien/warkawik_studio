#include "../headers/gamepch.h"

SelectComponent::SelectComponent(Actor *actor) : Component(actor),
                                                 mInputUtils(mOwner->getGame()->getInputUtils()),
                                                 mCamera(mOwner->getGame()->getRenderer()->getCamera())
{
}

SelectComponent::~SelectComponent() {}

void SelectComponent::update(float delta)
{
    glm::vec2 inputCoords = mInputUtils->getMouseMoveCoords();
    inputCoords += glm::vec2(mCamera->getPosition());

    if (inputCoords.x < (mOwner->getScale() + mOwner->getPosition().x) &&
        inputCoords.x > mOwner->getPosition().x - mOwner->getScale() &&
        inputCoords.y < (mOwner->getScale() + mOwner->getPosition().y) &&
        inputCoords.y > mOwner->getPosition().y - mOwner->getScale())
    {

        mOwner->getGame()->setHoveringActor(mOwner);

        if (mInputUtils->getClicked())
        {
            mOwner->getGame()->setSelectedActor(mOwner);
        }
    }
    else
    {
        if (mInputUtils->getClicked())
        {
            mOwner->getGame()->removeSelectedActor(mOwner);
        }
    }
}