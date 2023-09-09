#ifndef PART_H
#define PART_H

class Part : public Actor
{
public:
    Part(Game *game, unsigned int id);
    virtual ~Part();

    TransformComponent *getTransformComponent() { return mTransform; }
    void setSelected(bool selected) { mSelected = selected; }
    bool getSelected() { return mSelected; }

    unsigned int getId() { return mId; }

private:
    TransformComponent *mTransform;
    bool mSelected;
    unsigned int mId;
};

#endif