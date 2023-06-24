#include "../headers/gamepch.h"

Grid::Grid(Game *game) : Actor(game)
{
    mGridComponent = new GridComponent(this, this->getGame()->getRenderer());
}

Grid::~Grid()
{
}