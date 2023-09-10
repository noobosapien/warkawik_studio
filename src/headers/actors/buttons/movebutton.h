#ifndef MOVE_BUTTON_H
#define MOVE_BUTTON_H

class MoveButton : public Button
{
public:
    MoveButton(Game *game, unsigned int id);
    virtual ~MoveButton();

    virtual void execute() override;
    virtual void updateActor(float delta) override;

private:
};

#endif