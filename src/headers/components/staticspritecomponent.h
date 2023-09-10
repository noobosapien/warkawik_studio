#ifndef STATIC_SPRITE_COMPONENT_H
#define STATIC_SPRITE_COMPONENT_H

class StaticSpriteComponent : public RenderComponent
{

public:
    StaticSpriteComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 100);
    virtual ~StaticSpriteComponent();

    virtual void draw() override;
    virtual void setTexture(class Texture *texture);

    int getTexWidth() { return mTexWidth; }
    int getTexHeight() { return mTexHeight; }

private:
    class Texture *mTexture;
    glm::vec2 mPosition;
    float mScale;
    float mRotation;

    int mTexWidth;
    int mTexHeight;
};

#endif