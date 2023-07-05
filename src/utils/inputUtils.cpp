#include "../headers/gamepch.h"

InputUtils::InputUtils(Game *game) : mGame(game),
                                     mMouseMovementCoords(glm::vec2(0.f)),
                                     mPrevMouseCoords(glm::vec2(0.f)),
                                     mClicked(false),
                                     mClickedCoords(glm::vec2(0.f)),
                                     mToGo(glm::vec2(0.f))
{
    mCamera = mGame->getRenderer()->getCamera();
}

InputUtils::~InputUtils()
{
}

void InputUtils::clicked(const glm::vec2 &point)
{
    mClicked = true;
    mClickedCoords = MathUtils::changeWindowToGameCoords(point);
    mClickedCoords = glm::normalize(mClickedCoords);
}

void InputUtils::mouseMotion(const glm::vec2 &point)
{
    mMouseMovementCoords = MathUtils::changeWindowToGameCoords(point);

    if (mClicked)
    {
        glm::vec2 difference = mMouseMovementCoords - mPrevMouseCoords;
        difference = glm::normalize(difference);

        if (std::isnan(difference.x) || std::isnan(difference.y))
        {
            return;
        }

        mToGo = difference / 100.f;
        // mToGo.y *= -1;

        mCamera->setPosition(mCamera->getPosition() + glm::vec3(mToGo, 0.0));
        mPrevMouseCoords = mMouseMovementCoords;
    }
}

void InputUtils::unclicked()
{
    mClicked = false;
}