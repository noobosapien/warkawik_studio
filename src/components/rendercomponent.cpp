#include "../headers/gamepch.h"

RenderComponent::RenderComponent(class Actor *owner, class Renderer *renderer, int drawOrder) : Component(owner),
                                                                                                mDrawOrder(drawOrder),
                                                                                                mRenderer(renderer),
                                                                                                mVisible(true)
{
}

RenderComponent::~RenderComponent()
{
}
