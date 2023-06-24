#ifndef GRID_H
#define GRID_H

class Grid : public Actor
{
public:
    Grid(Game *game);
    virtual ~Grid();

private:
    class GridComponent *mGridComponent;
};

#endif