#pragma once
#include "../SceneBase.h"
#include"../../Object/Score.h"

// ゲームの状態を定義
enum class eGameState {
    ePlaying,       // プレイ中
    eTimeUp,        // タイムアップ
    eToResult       // リザルト画面へ遷移
};

class InGameScene :
    public SceneBase

{
private:
    Score* score = new Score;
    class EventLine* event_line;
    class NeedleAndPatient* n_and_p_black;//注射と患者のクラス
    class NeedleAndPatient* n_and_p_gray;//注射と患者のクラス
	int time;                       // 時間を保持する変数
	unsigned int previousTime;      // 前回の時間を保持する変数
    unsigned int countdown_after_timeup;
    bool time_up_flag;
    eGameState gameState;// ゲームの状態を保持する変数

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

private:
    //n_and_pのラインのｙ座標を返す
    int GetStopLine();
    //n_and_pのどちらがアップデート開始するかを判断する関数
    void Start_NAndP();
};

