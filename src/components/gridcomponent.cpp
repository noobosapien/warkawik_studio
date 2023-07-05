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

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());

        glm::vec2 offset = mRenderer->getCamera()->getPosition() * 300.f;
        // offset.y *= -1.f;

        mShader->setVec2Uniform("u_offset", offset);
        mShader->setVec2Uniform("u_pitch", glm::vec2(60, 60));

        // std::cout << mRenderer->getCamera()->getPosition().x << ", " << mRenderer->getCamera()->getPosition().y << std::endl;
    }
}