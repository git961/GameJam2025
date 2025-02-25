#pragma once
#include "../SceneBase.h"

class HelpScene :
    public SceneBase
{
private:
    int HelpImage;
public:
    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;
    int BGM;
    int SE;

public:
    virtual eSceneType GetNowSceneType() const override;
};

