#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

class RenderComponent : public Component
{

public:
    RenderComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 100);
    virtual ~RenderComponent();

    virtual void draw() = 0;

    int getDrawOrder() { return mDrawOrder; }

    inline bool getVisible() { return mVisible; }
    inline void setVisible(bool visible) { mVisible = visible; }

protected:
    Renderer *mRenderer;
    Shader *mShader;
    int mDrawOrder;
    bool mVisible;
};

#endif