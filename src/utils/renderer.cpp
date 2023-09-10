#include "../headers/gamepch.h"

int Renderer::WIN_WIDTH = 800;
int Renderer::WIN_HEIGHT = 800;
int Renderer::GAME_WIDTH = 800;
int Renderer::GAME_HEIGHT = 800;
glm::vec2 Renderer::WIN_RES = glm::vec2(1.0);

Renderer::Renderer() : mCamera(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::initialize(int width, int height)
{
    if (mCamera == nullptr)
    {
        mCamera = new Camera;
    }

    SDL_Init(SDL_INIT_VIDEO);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::deinitialize()
{
    for (auto i : mTextures)
    {
        i.second->unload();
        delete i.second;
    }

    mTextures.clear();
    delete mCamera;
}

void Renderer::setWinDim(int width, int height)
{
    if (height > width)
    {
        Renderer::GAME_HEIGHT = height;
        Renderer::GAME_WIDTH = height;

        Renderer::WIN_HEIGHT = height;
        Renderer::WIN_WIDTH = width;
        Renderer::WIN_RES = glm::vec2(1.0, (float)height / width);

        SDL_SetWindowSize(window, width, height);
        glViewport(-height / 2 + width / 2, 0, height, height);
    }
    else
    {
        Renderer::GAME_HEIGHT = width;
        Renderer::GAME_WIDTH = width;

        Renderer::WIN_HEIGHT = height;
        Renderer::WIN_WIDTH = width;
        Renderer::WIN_RES = glm::vec2((float)width / height, 1.0);

        SDL_SetWindowSize(window, width, height);
        // glViewport(0, -width/2 + height/2, width, width);
        glViewport(0, -width / 2 + height / 2, width, width);
    }
}

void Renderer::update()
{
    glClearColor(0.196, 0.161, 0.278, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (auto obj : mRenders)
    {
        obj->draw();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    SDL_GL_SwapWindow(window);
}

Shader *Renderer::getShader(const std::string &name)
{
    if (mShaders[name])
        return mShaders[name];

    return nullptr;
}

Texture *Renderer::getTexture(const std::string &filename)
{
    Texture *tex = nullptr;

    auto iter = mTextures.find(filename);

    if (iter != mTextures.end())
        tex = iter->second;
    else
    {
        tex = new Texture();

        if (tex->load(filename))
            mTextures.emplace(filename, tex);
        else
        {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

void Renderer::insertObject(class RenderComponent *render, unsigned int drawOrder)
{
    auto iter = mRenders.begin();

    for (; iter != mRenders.end(); ++iter)
    {
        if (drawOrder < (*iter)->getDrawOrder())
            break;
    }
    mRenders.insert(iter, render);
}

void Renderer::removeObject(class RenderComponent *render)
{
    auto iter = std::find(mRenders.begin(), mRenders.end(), render);
    if (iter != mRenders.end())
    {
        mRenders.erase(iter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

bool Renderer::loadShaders()
{
    if (!loadSpriteShader())
        return false;

    if (!loadSpriteSelectedShader())
        return false;

    if (!loadStaticSpriteShader())
        return false;

    if (!loadChargingShader())
        return false;

    if (!loadLightningShader())
        return false;

    if (!loadGridShader())
        return false;

    return true;
}

bool Renderer::loadGridShader()
{
    auto mGridShader = new Shader();

    if (!mGridShader->load("src/shaders/grid.vert", "src/shaders/grid.frag"))
    {
        return false;
    }

    mGridShader->setActive();

    float vertices[] = {-1.0, 1.0,
                        1.0, 1.0,
                        1.0, -1.0,
                        -1.0, -1.0};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mGridShader->setVertexData(vertices, 4, indices, 6, 2);

    mGridShader->setAttrib("a_position", 2, 2, 0);

    mShaders["grid"] = mGridShader;

    return true;
}

bool Renderer::loadSpriteShader()
{
    auto mSpriteShader = new Shader();

    if (!mSpriteShader->load("src/shaders/sprite.vert", "src/shaders/sprite.frag"))
    {
        return false;
    }

    mSpriteShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mSpriteShader->setVertexData(vertices, 4, indices, 6, 5);

    mSpriteShader->setAttrib("a_position", 3, 5, 0);
    mSpriteShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["sprite"] = mSpriteShader;

    return true;
}

bool Renderer::loadSpriteSelectedShader()
{
    auto mSpriteSelectedShader = new Shader();

    if (!mSpriteSelectedShader->load("src/shaders/sprite.vert", "src/shaders/sprite_selected.frag"))
    {
        return false;
    }

    mSpriteSelectedShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mSpriteSelectedShader->setVertexData(vertices, 4, indices, 6, 5);

    mSpriteSelectedShader->setAttrib("a_position", 3, 5, 0);
    mSpriteSelectedShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["sprite_selected"] = mSpriteSelectedShader;

    return true;
}

bool Renderer::loadStaticSpriteShader()
{
    auto mStaticSpriteShader = new Shader();

    if (!mStaticSpriteShader->load("src/shaders/static_sprite.vert", "src/shaders/static_sprite.frag"))
    {
        return false;
    }

    mStaticSpriteShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mStaticSpriteShader->setVertexData(vertices, 4, indices, 6, 5);

    mStaticSpriteShader->setAttrib("a_position", 3, 5, 0);
    mStaticSpriteShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["static_sprite"] = mStaticSpriteShader;

    return true;
}

bool Renderer::loadChargingShader()
{
    auto mChargingShader = new Shader();

    if (!mChargingShader->load("src/shaders/charging.vert", "src/shaders/charging.frag"))
    {
        return false;
    }

    mChargingShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mChargingShader->setVertexData(vertices, 4, indices, 6, 5);

    mChargingShader->setAttrib("a_position", 3, 5, 0);
    mChargingShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["charging"] = mChargingShader;

    return true;
}

bool Renderer::loadLightningShader()
{
    auto mLightningShader = new Shader();

    if (!mLightningShader->load("src/shaders/lightning.vert", "src/shaders/lightning.frag"))
    {
        return false;
    }

    mLightningShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mLightningShader->setVertexData(vertices, 4, indices, 6, 5);

    mLightningShader->setAttrib("a_position", 3, 5, 0);
    mLightningShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["lightning"] = mLightningShader;

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////