#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

struct Transform
{
    glm::vec3 position;
    glm::vec3 scale;
    Quat rotation;
};

class TransformComponent : public Component
{

public:
    TransformComponent(class Actor *owner);
    virtual ~TransformComponent();

    void updateInfo();

    void changePosition(glm::vec3 position);
    void changeScale(glm::vec3 scale);

    void changeRotation(Quat rotation);
    void changeRotation(float rotation);

    const Transform &getTransform() { return mTransform; }
    void setTransform(Transform transform);

    static Transform combine(const Transform &a, const Transform &b);
    static Transform inverse(const Transform &t);
    static Transform mix(const Transform &a, const Transform &b, float t);

protected:
private:
    Transform mTransform;

    void updateOwner();
};

#endif