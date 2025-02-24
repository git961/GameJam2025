#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Object/EventLine.h"
#include "../../Object/NeedleAndPatient.h"
#include "DxLib.h"

// 1秒あたりのミリ秒数
const int MILLISECONDS_PER_SECOND = 1000;

InGameScene::InGameScene() :
    time(10),                    // ここで制限時間を変更できます
    
    countdown_after_timeup(0),   // タイムアップ後のカウントダウン時間 
    gameState(eGameState::ePlaying) // ゲーム状態の初期化
{
    event_line = new EventLine();
    n_and_p_black = new NeedleAndPatient(event_line, 0);
    n_and_p_gray = new NeedleAndPatient(event_line, 1);
    InGameImage = LoadGraph("Resource/Image/InGame/InGame.png");
    patient_count = 0;
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
    patient_count = 0;
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
        //score->Update();

        //スコアを加算してもよかったら
        if (CheckAddScoreNAndP() == true)
        {
            score->AddScore(GetRedLine(), event_line->GetLineStopY());
            patient_count++;
        }
        Start_NAndP();
        break;

    case eGameState::eTimeUp://タイムアップの場合

        if (elapsedTime >= MILLISECONDS_PER_SECOND) {// 1秒以上経過した場合
            countdown_after_timeup--;
            previousTime = currentTime;// 前回の時間を更新

            if (countdown_after_timeup <= 0) {
                SaveNewScore();
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
    DrawFormatString(10, 10, GetColor(0, 0, 0),"patient_cnt%d\n",patient_count);
    DrawFormatString(10, 30, GetColor(0, 0, 0),"total_score%d\n",score->GetTotalScore());

    event_line->Draw();
    n_and_p_black->Draw();
    n_and_p_gray->Draw();

    score->Draw();

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

int InGameScene::GetRedLine()
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

bool InGameScene::CheckAddScoreNAndP()
{
    if (n_and_p_black->CheckAddScore() == true)
    {
        return true;
    }

    if (n_and_p_gray->CheckAddScore() == true)
    {
        return true;
    }

    return false;
}

void InGameScene::SaveNewScore()
{

    int save_score = score->GetTotalScore();

    string txt_file_path = "C:\\GameJam2025\\GameJam2025\\GameJam\\Resource\\Ranking\\Ranking.txt";
    ofstream ofs_txt_file(txt_file_path, std::ios::app);//std::ios::appで末尾に記入毎回保存は３つだけで良いはず
    if (ofs_txt_file.is_open()) {
        ofs_txt_file << patient_count << ',' << save_score;
        ofs_txt_file.close();
    }
}
