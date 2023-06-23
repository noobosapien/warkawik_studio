#ifndef PART_H
#define PART_H

class Part : public Actor
{
public:
    Part(Game *game);
    virtual ~Part();

    TransformComponent *getTransformComponent() { return mTransform; }

private:
    TransformComponent *mTransform;
};

#endif