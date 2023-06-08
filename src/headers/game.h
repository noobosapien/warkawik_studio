#ifndef GAME_H
#define GAME_H

class Game : public Engine
{
public:
    Game();
    bool initialize();
    void runLoop();
    bool shutDown();
    void startGame();

    enum GameState
    {
        EStart,
        EGameplay,
        EPause
    };

    enum Globals
    {
    };

    void addActor(Actor *actor);
    void removeActor(Actor *actor);

    static bool DEBUG;

    void setValue(std::string key, std::string value);
    std::string getValue(Globals key);

    void callUIRPC(std::string command);

private:
    void processInput();
    void updateGame() override;
    void generateOutput() override;

    void loadData();
    void unloadData();

    void loadNetwork(int pid, char *name);

    GameState mState;
    bool mConnected;

    std::vector<Actor *> mActors;
    std::vector<Actor *> mPendingActors;
    bool mUpdatingActors;

    class Utils *mUtils;
};

#endif