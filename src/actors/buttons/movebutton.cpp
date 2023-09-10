#include "../../headers/gamepch.h"

MoveButton::MoveButton(Game *game, unsigned int id) : Button(game, id)
{
    new ClickComponent(this);
}

MoveButton::~MoveButton()
{
}

void MoveButton::execute()
{
}

void MoveButton::updateActor(float delta)
{
    if (getGame()->getSelectedActor() == nullptr)
    {
        setVisible(false);
    }
    else
    {
        setVisible(true);
    }
}