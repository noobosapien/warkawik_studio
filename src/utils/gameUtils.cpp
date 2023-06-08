#include "../headers/gamepch.h"

Utils::Utils(Game *game) : mGame(game)
{
    initialize();
}

Utils::~Utils()
{
    mUICommands.clear();
}

void Utils::callUIRPC(std::string command)
{
    UICalls method = mUICommands[command];

    // change everything to globals

    switch (method)
    {
    case UICalls::PLAYER_MOVE_LEFT: // this is called when the command is not found

        break;

    case UICalls::PLAYER_MOVE_RIGHT:

        break;

    case UICalls::PLAYER_MOVE_STOP:

        break;

    case UICalls::PLAYER_ROTATE_LEFT:

        break;

    case UICalls::PLAYER_ROTATE_RIGHT:

        break;

    case UICalls::PLAYER_ROTATE_STOP:

        break;

    case UICalls::PLAYER_SHOOT_START:

        break;

    case UICalls::PLAYER_SHOOT_STOP:

        break;

    case UICalls::PLAYER_SELECT_GUN1:

        break;

    case UICalls::PLAYER_SELECT_GUN2:

        break;

    default:
        break;
    }
}

void Utils::initialize()
{
    initializeUICommands();
}

void Utils::initializeUICommands()
{
    addUICommand("PLAYER_MOVE_LEFT", UICalls::PLAYER_MOVE_LEFT);
    addUICommand("PLAYER_MOVE_RIGHT", UICalls::PLAYER_MOVE_RIGHT);
    addUICommand("PLAYER_MOVE_STOP", UICalls::PLAYER_MOVE_STOP);

    addUICommand("PLAYER_ROTATE_LEFT", UICalls::PLAYER_ROTATE_LEFT);
    addUICommand("PLAYER_ROTATE_RIGHT", UICalls::PLAYER_ROTATE_RIGHT);
    addUICommand("PLAYER_ROTATE_STOP", UICalls::PLAYER_ROTATE_STOP);

    addUICommand("PLAYER_SHOOT_START", UICalls::PLAYER_SHOOT_START);
    addUICommand("PLAYER_SHOOT_STOP", UICalls::PLAYER_SHOOT_STOP);

    addUICommand("PLAYER_SELECT_GUN1", UICalls::PLAYER_SELECT_GUN1);
    addUICommand("PLAYER_SELECT_GUN2", UICalls::PLAYER_SELECT_GUN2);
}

void Utils::addUICommand(std::string name, UICalls method)
{
    mUICommands[name] = method;
}

template <typename T>
T Curves::cubic_bezier(T a, T b, T c, T d, float time)
{
    return (time * time * time * (-a + 2 * b - 2 * c + d)) +
           (time * time * (3 * a - 6 * b + 3 * c)) +
           (time * (-3 * a + 3 * b)) + c;
}

float Curves::f_cubic_bezier(float a, float b, float c, float d, float time)
{
    return cubic_bezier(a, b, c, d, time);
}

template <typename T>
T Curves::linearInterpolate(T value, T to, float time)
{
    return value + (to - value) * time;
}

float Curves::f_linearInterpolate(float value, float to, float time)
{
    return linearInterpolate(value, to, time);
}