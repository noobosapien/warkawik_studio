#ifndef PART_H
#define PART_H

class Part : public Actor
{
public:
    Part(Game *game);
    virtual ~Part();

    TransformComponent *getTransformComponent() { return mTransform; }
    void setSelected(bool selected) { mSelected = selected; }
    bool getSelected() { return mSelected; }

private:
    TransformComponent *mTransform;
    bool mSelected;
};

#endif