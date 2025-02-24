#pragma once
#include "../SceneBase.h"
class ResultScene :
    public SceneBase
{
private:
    class Score* score;

public:
    ResultScene();
    ~ResultScene();

    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;

public:
    virtual eSceneType GetNowSceneType() const override;

};

