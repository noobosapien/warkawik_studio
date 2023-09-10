#include "headers/gamepch.h"

Game::Game() : mState(EStart),
               mUtils(nullptr),
               mInputUtils(nullptr),
               mSelectedActor(nullptr),
               mHoveringActor(nullptr),
               lastId(1)
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

    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {
        case SDL_FINGERDOWN:
            continue;

        case SDL_FINGERMOTION:
            continue;

        case SDL_MOUSEBUTTONDOWN:
            mInputUtils->clicked(glm::vec2(event.motion.x, event.motion.y));
            continue;

        case SDL_MOUSEMOTION:
            mInputUtils->mouseMotion(glm::vec2(event.motion.x, event.motion.y));
            continue;

        case SDL_MOUSEBUTTONUP:
            mInputUtils->unclicked();
            continue;

        default:
            continue;
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

    new Grid(this);
    mUtils = new Utils(this);
    mInputUtils = new InputUtils(this);

    Part *face = new Part(this, lastId++);
    SpriteComponent *sc = new SpriteComponent(face, this->getRenderer());
    sc->setTexture(getRenderer()->getTexture("src/assets/textures/face.png"));
    face->setScale(0.2);
    face->setPosition(glm::vec2(1.0, -1.0));

    Part *body = new Part(this, lastId++);
    SpriteComponent *sc1 = new SpriteComponent(body, this->getRenderer());
    sc1->setTexture(getRenderer()->getTexture("src/assets/textures/body.png"));
    body->setScale(0.2);

    MoveButton *mb = new MoveButton(this, lastId++);
    SpriteComponent *sc2 = new SpriteComponent(mb, this->getRenderer());
    sc2->setTexture(getRenderer()->getTexture("src/assets/textures/move.png"));

    mb->setNormalSprite(sc2);
    mb->setHoveringSprite(sc2);
    mb->setClickedSprite(sc2);
    mb->setScale(0.05);
    mb->setPosition(glm::vec2(-0.7, 0.7));
    mb->setVisible(true);

    auto tsb = body->getTransformComponent();
    auto tsf = face->getTransformComponent();
    tsb->updateInfo();
    tsf->updateInfo();
    mb->getTransformComponent()->updateInfo();
    // tsb->setTransform(TransformComponent::combine(tsb->getTransform(), tsf->getTransform()));
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

void Game::setSelectedActor(Actor *actor)
{
    if (mSelectedActor)
    {
        ((class Part *)mSelectedActor)->setSelected(false);
    }

    mSelectedActor = actor;
    ((class Part *)mSelectedActor)->setSelected(true);
}

void Game::removeSelectedActor(Actor *actor)
{
    if (mSelectedActor)
    {
        if (((class Part *)mSelectedActor)->getId() == ((class Part *)actor)->getId())
        {
            ((class Part *)mSelectedActor)->setSelected(false);
            mSelectedActor = nullptr;
        }
    }
}