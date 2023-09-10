#ifndef BUTTON_H
#define BUTTON_H

class Button : public Actor
{
public:
    Button(Game *game, unsigned int id);
    virtual ~Button();

    TransformComponent *getTransformComponent() { return mTransform; }
    unsigned int getId() { return mId; }

    virtual void execute() = 0;

    inline virtual void setVisible(bool visible)
    {
        mVisible = visible;

        if (!visible)
        {
            mNormalSprite->setVisible(false);
            mHoveringSprite->setVisible(false);
            mClickedSprite->setVisible(false);
        }
        else
        {
            mNormalSprite->setVisible(true);
        }
    }
    inline bool getVisible() { return mVisible; }

    inline void setNormalSprite(SpriteComponent *sprite)
    {
        mNormalSprite = sprite;
        mNormalSprite->setVisible(true);
    }

    inline void setHoveringSprite(SpriteComponent *sprite)
    {
        mHoveringSprite = sprite;
        mHoveringSprite->setVisible(false);
    }

    inline void setClickedSprite(SpriteComponent *sprite)
    {
        mClickedSprite = sprite;
        mClickedSprite->setVisible(false);
    }

protected:
    bool mVisible;
    SpriteComponent *mNormalSprite;
    SpriteComponent *mHoveringSprite;
    SpriteComponent *mClickedSprite;

private:
    TransformComponent *mTransform;
    unsigned int mId;
};

#endif