#ifndef SELECT_COMPONENT_H
#define SELECT_COMPONENT_H

class SelectComponent : public Component
{

public:
    SelectComponent(class Actor *owner);
    virtual ~SelectComponent();

    virtual void update(float delta) override;

private:
    InputUtils *mInputUtils;
    Camera *mCamera;
};

#endif