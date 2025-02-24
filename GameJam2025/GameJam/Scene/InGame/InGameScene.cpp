#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Object/EventLine.h"
#include "../../Object/NeedleAndPatient.h"
#include "DxLib.h"

// 1秒あたりのミリ秒数
const int MILLISECONDS_PER_SECOND = 1000;

InGameScene::InGameScene() :
    time(60),                    // ここで制限時間を変更できます
    
    countdown_after_timeup(0),   // タイムアップ後のカウントダウン時間 
    gameState(eGameState::ePlaying) // ゲーム状態の初期化
{
    event_line = new EventLine();
    n_and_p_black = new NeedleAndPatient(event_line, 0);
    n_and_p_gray = new NeedleAndPatient(event_line, 1);
    InGameImage = LoadGraph("Resource/Image/InGame/InGame.png");
}

InGameScene::~InGameScene()
{
    // 各オブジェクトの解放
    delete event_line;
    delete n_and_p_black;
    delete n_and_p_gray;
    delete score; 
}

void InGameScene::Initialize()
{
    score->Initialize();              // スコアの初期化
    previousTime = GetNowCount();     // 前回の時間を初期化
    countdown_after_timeup = 5;       // カウントダウン初期化
    gameState = eGameState::ePlaying; // ゲーム状態をプレイ中に初期化
}

eSceneType InGameScene::Update()
{
    PadInputManager* pad_input = PadInputManager::GetInstance();

    // 現在の時間を取得
    unsigned int currentTime = GetNowCount();
    // 前回のフレームからの経過時間を計算
    unsigned int elapsedTime = currentTime - previousTime;

    // ゲームの状態に応じて処理を分岐
    switch (gameState) {
    case eGameState::ePlaying:// プレイ中の場合
        if (elapsedTime >= MILLISECONDS_PER_SECOND) {// 1秒以上経過した場合
            time--;
            previousTime = currentTime;// 前回の時間を更新

            if (time <= 0) {
                time = 0;
                gameState = eGameState::eTimeUp;
                previousTime = currentTime; // カウントダウン開始時間を記録
            }
        }
        // 各オブジェクトの更新
        event_line->Update();
        n_and_p_black->Update();
        n_and_p_gray->Update();
        score->Update();

        Start_NAndP();
        break;

    case eGameState::eTimeUp://タイムアップの場合

        if (elapsedTime >= MILLISECONDS_PER_SECOND) {// 1秒以上経過した場合
            countdown_after_timeup--;
            previousTime = currentTime;// 前回の時間を更新

            if (countdown_after_timeup <= 0) {
                gameState = eGameState::eToResult;// ゲーム状態をリザルト画面遷移に変更
                return eSceneType::eResult; // リザルト画面に移行
            }
        }
        break;

    case eGameState::eToResult:// リザルト画面遷移の場合
        return eSceneType::eResult; // リザルト画面に遷移
    }

    return __super::Update();
}

void InGameScene::Draw() const
{
    DrawGraph(0, 0, InGameImage, TRUE);
    __super::Draw();
    DrawString(10, 10, "InGame\n", GetColor(255, 255, 255));
    DrawString(10, 26, "B:Result", GetColor(255, 255, 255));

    event_line->Draw();
    n_and_p_black->Draw();
    n_and_p_gray->Draw();

    // ゲーム状態に応じて描画内容を切り替え

    if (gameState == eGameState::ePlaying) {// プレイ中の場合
        DrawFormatString(10, 50, GetColor(255, 255, 255), "残り時間 : %d", time);
    }
    else if (gameState == eGameState::eTimeUp) {// タイムアップの場合
        DrawFormatString(300, 400, GetColor(255, 255, 255), "End %d", countdown_after_timeup);
    }
}

void InGameScene::Finalize()
{
    __super::Finalize();
}

eSceneType InGameScene::GetNowSceneType() const
{
    return eSceneType::eInGame;
}

int InGameScene::GetStopLine()
{
    if (n_and_p_black->IsRetrunY())
    {
        return n_and_p_black->GetStopY();
    }

    if (n_and_p_gray->IsRetrunY())
    {
        return n_and_p_gray->GetStopY();
    }

    return 0;
}

void InGameScene::Start_NAndP()
{
    if (n_and_p_black->CheckNextStart())
    {
        n_and_p_gray->SetStart();
    }

    if (n_and_p_gray->CheckNextStart())
    {
        n_and_p_black->SetStart();
    }
}