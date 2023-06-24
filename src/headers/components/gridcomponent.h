#ifndef GRID_COMPONENT_H
#define GRID_COMPONENT_H

class GridComponent : public RenderComponent
{

public:
    GridComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 90);
    virtual ~GridComponent();

    virtual void draw() override;

private:
};

#endif