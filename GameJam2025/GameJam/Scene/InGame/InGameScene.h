#pragma once
#include "../SceneBase.h"
#include"../../Object/Score.h"

class InGameScene :
    public SceneBase
{
private:
    Score* score = new Score;
    class EventLine* event_line;

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

