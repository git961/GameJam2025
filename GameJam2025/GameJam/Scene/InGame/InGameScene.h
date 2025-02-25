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

    // 画像・BGM関連
    int InGameImage;        // 背景画像
    int InGameBGM;          // BGM
    int numberImage[11];    // 数字画像 (0～9)
    int End;
    int Start;
    int BGM;
    int SE;
    int SE2;
    bool se_once;//seを一回だけ鳴らす用

    Score* score = new Score;
    class EventLine* event_line;
    class NeedleAndPatient* n_and_p_black;//注射と患者のクラス
    class NeedleAndPatient* n_and_p_gray;//注射と患者のクラス
    class Column* back_column;//背景の列
   // int InGameImage;
	int time;                       // 時間を保持する変数
	unsigned int previousTime;      // 前回の時間を保持する変数
    unsigned int countdown_after_timeup;
   int  countdown_delay;
    bool time_up_flag;
    eGameState gameState;// ゲームの状態を保持する変数

    int patient_count;//さばいた人数のカウント

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
    int GetRedLine();
    //n_and_pのどちらがアップデート開始するかを判断する関数
    void Start_NAndP();
    //スコアを加算するかチェック
    bool CheckAddScoreNAndP();
    void SaveNewScore();

};

