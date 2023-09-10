#ifndef CLICK_COMPONENET
#define CLICK_COMPONENET

class ClickComponent : public Component
{
public:
    ClickComponent(Actor *owner);
    ~ClickComponent();

    virtual void update(float delta) override;

private:
};

#endif