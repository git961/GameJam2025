#pragma once
#include "../SceneBase.h"

class InGameScene :
    public SceneBase
{
private:

public:
    InGameScene();
    virtual ~InGameScene();

public:
    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;

public:
    virtual eSceneType GetNowSceneType() const override;
};

