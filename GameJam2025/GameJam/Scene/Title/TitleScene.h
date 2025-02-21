#pragma once
#include "../SceneBase.h"

class TitleScene :
    public SceneBase
{
private:
    int cursor_number;
    int arrow_image;
    int cursor_y;


public:
    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;
    virtual void SelectCursor();

public:
    virtual eSceneType GetNowSceneType() const override;
};

