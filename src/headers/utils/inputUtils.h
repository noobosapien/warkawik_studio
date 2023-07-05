#ifndef GAME_INPUT_UTILS_H
#define GAME_INPUT_UTILS_H

class InputUtils
{
public:
    InputUtils(Game *game);
    ~InputUtils();

    void clicked(const glm::vec2 &point);
    void mouseMotion(const glm::vec2 &point);
    void unclicked();

private:
    Game *mGame;
    Camera *mCamera;

    bool mClicked = false;

    glm::vec2 mMouseMovementCoords;
    glm::vec2 mPrevMouseCoords;
    glm::vec2 mClickedCoords;
    glm::vec2 mToGo;
};

#endif