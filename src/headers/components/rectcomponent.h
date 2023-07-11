#ifndef RECTCOMPONENET
#define RECTCOMPONENET

class RectangleComponent : public Component
{
public:
    RectangleComponent(Actor *owner, glm::vec2 position, float rotation, glm::vec2 size);
    ~RectangleComponent();

    void changePosition(const glm::vec2 &position);
    void changeRotation(float rotation);
    void changeSize(const glm::vec2 &size);

private:
    glm::vec2 mPosition;
    float mRotation;
    glm::vec2 mSize;

    bool checkCollisionWithPoint(const glm::vec2 &point);
};

#endif