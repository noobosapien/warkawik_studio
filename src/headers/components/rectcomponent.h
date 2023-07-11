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

    glm::vec2 mA;
    glm::vec2 mB;
    glm::vec2 mC;
    glm::vec2 mD;

    glm::vec3 mPlaneAB;
    glm::vec3 mPlaneBC;
    glm::vec3 mPlaneCD;
    glm::vec3 mPlaneAD;

    void init();
    bool checkCollisionWithPoint(const glm::vec2 &point);
    void recomputePlanes();
};

#endif