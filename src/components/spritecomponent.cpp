#include "../headers/gamepch.h"

SpriteComponent::SpriteComponent(Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner, renderer, drawOrder),
                                                                                    mTexture(nullptr),
                                                                                    mTexWidth(0),
                                                                                    mTexHeight(0)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("sprite");
    mSelectedShader = mRenderer->getShader("sprite_selected");
}

SpriteComponent::~SpriteComponent()
{
    mRenderer->removeObject(this);
}

void SpriteComponent::draw()
{

    if (mTexture && mShader && mVisible)
    {
        if (((class Part *)mOwner)->getSelected())
        {
            mSelectedShader->setActive();
            glm::mat4 model = glm::mat4(1.f);

            model = mOwner->getWorldTransform();

            mSelectedShader->setMatrixUniform("u_model", model);
            mSelectedShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());
        }
        else
        {
            mShader->setActive();
            glm::mat4 model = glm::mat4(1.f);

            model = mOwner->getWorldTransform();

            mShader->setMatrixUniform("u_model", model);
            mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());
        }

        mTexture->setActive();
    }
}

void SpriteComponent::setTexture(class Texture *texture)
{
    mTexture = texture;

    mTexWidth = texture->getWidth();
    mTexHeight = texture->getHeight();
}