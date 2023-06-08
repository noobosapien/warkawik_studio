#include "headers/gamepch.h"

Game::Game() : mState(EStart)
{
}

bool Game::DEBUG = false;

bool Game::initialize()
{
    Engine::initialize(800, 800);

    return true;
}

void Game::runLoop()
{
    processInput();
    updateGame();
    generateOutput();
}

bool Game::shutDown()
{
    Engine::shutDown();

    return true;
}

void Game::startGame()
{

    if (!mRenderer->loadShaders())
    {
        printf("Failed to load shaders\n");
        return;
    }

    loadData();

    mState = EGameplay;
}

// private

void Game::processInput()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        default:
            break;
        }
    }
}

void Game::updateGame()
{
    Engine::updateGame();

    if (mState == EGameplay)
    {

        // Actor stuff

        mUpdatingActors = true;
        for (auto actor : mActors)
        {
            actor->update(this->mDeltaTime);
        }
        mUpdatingActors = false;

        for (auto pending : mPendingActors)
        {
            pending->computeWorldTransform();
            mActors.emplace_back(pending);
        }
        mPendingActors.clear();

        std::vector<Actor *> deadActors;
        for (auto actor : mActors)
        {
            if (actor->getState() == Actor::EDead)
            {
                deadActors.emplace_back(actor);
            }
        }

        for (auto actor : deadActors)
        {
            delete actor;
        }
    }
}

void Game::generateOutput()
{
    Engine::generateOutput();
}

void Game::loadData()
{
    Actor *face = new Actor(this);
    SpriteComponent *sc = new SpriteComponent(face, this->getRenderer());
    sc->setTexture(getRenderer()->getTexture("src/assets/textures/face.png"));
    face->setScale(0.1);
    face->setPosition(glm::vec2(0.0, 0.2));

    Actor *body = new Actor(this);
    SpriteComponent *sc1 = new SpriteComponent(body, this->getRenderer());
    sc1->setTexture(getRenderer()->getTexture("src/assets/textures/body.png"));
    body->setScale(0.2);

    mUtils = new Utils(this);
}

void Game::loadNetwork(int pid, char *name)
{
}

void Game::unloadData()
{

    while (!mActors.empty())
    {
        delete mActors.back();
    }

    if (mUtils)
        delete mUtils;
}

void Game::addActor(Actor *actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::removeActor(Actor *actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::setValue(std::string key, std::string value)
{

    // if (key == "PLAYER_SPEED")
    //     mDataStore[Globals::GPlayerSpeed] = value;
}

void Game::callUIRPC(std::string command)
{
    mUtils->callUIRPC(command);
}
