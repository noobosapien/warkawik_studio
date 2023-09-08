#include "../headers/gamepch.h"

SelectComponent::SelectComponent(Actor *actor) : Component(actor),
                                                 mInputUtils(mOwner->getGame()->getInputUtils())
{
}

SelectComponent::~SelectComponent() {}

void SelectComponent::update(float delta)
{
    glm::vec2 inputCoords = mInputUtils->getMouseMoveCoords();
    // std::cout << inputCoords.x << ", " << inputCoords.y << std::endl;

    if (inputCoords.x < (mOwner->getScale() + mOwner->getPosition().x) &&
        inputCoords.x > mOwner->getPosition().x - mOwner->getScale() &&
        inputCoords.y < (mOwner->getScale() + mOwner->getPosition().y) &&
        inputCoords.y > mOwner->getPosition().y - mOwner->getScale())
    {
        std::cout << inputCoords.x << ", " << inputCoords.y << "  "
                  << mInputUtils->getClicked()
                  << std::endl;

        mOwner->getGame()->setHoveringActor(mOwner);

        // if (mInputUtils->getClicked())
        // {
        //     mOwner->getGame()->setSelectedActor(mOwner);
        // }
    }
}