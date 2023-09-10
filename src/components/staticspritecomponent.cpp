#include "../headers/gamepch.h"

StaticSpriteComponent::StaticSpriteComponent(Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner, renderer, drawOrder),
                                                                                                mTexture(nullptr),
                                                                                                mTexWidth(0),
                                                                                                mTexHeight(0)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("static_sprite");

    mPosition = mOwner->getPosition();
    mRotation = mOwner->getRotation();
    mScale = mOwner->getScale();
}

StaticSpriteComponent::~StaticSpriteComponent()
{
    mRenderer->removeObject(this);
}

void StaticSpriteComponent::draw()
{

    if (mTexture && mShader && mVisible)
    {

        mShader->setActive();
        glm::mat4 model = glm::mat4(1.f);
        glm::vec3 v = mRenderer->getCamera()->getPosition();

        mPosition = mOwner->getPosition();
        mRotation = mOwner->getRotation();
        mScale = mOwner->getScale();

        model = glm::translate(model, glm::vec3(mPosition.x + v.x, mPosition.y + v.y, 0.f));
        model = glm::rotate(model, glm::radians(mRotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::scale(model, glm::vec3(mScale, mScale, mScale));

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());

        mTexture->setActive();
    }
}

void StaticSpriteComponent::setTexture(class Texture *texture)
{
    mTexture = texture;

    mTexWidth = texture->getWidth();
    mTexHeight = texture->getHeight();
}