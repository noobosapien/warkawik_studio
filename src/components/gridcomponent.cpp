#include "../headers/gamepch.h"

GridComponent::GridComponent(Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner, renderer, drawOrder)

{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("grid");
}

GridComponent::~GridComponent()
{
    mRenderer->removeObject(this);
}

void GridComponent::draw()
{

    if (mShader)
    {

        mShader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        mShader->setVec2Uniform("u_offset", glm::vec2(-0.1, 0.1));
        mShader->setVec2Uniform("u_pitch", glm::vec2(64, 64));

        mShader->setFloatUniform("u_vpw", 600);
        mShader->setFloatUniform("u_vph", 600);
    }
}