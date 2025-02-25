#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Object/EventLine.h"
#include "../../Object/NeedleAndPatient.h"
#include "../../Object/Column.h"
#include "DxLib.h"

// 1秒あたりのミリ秒数
const int MILLISECONDS_PER_SECOND = 1000;

InGameScene::InGameScene() :
    time(30),    // ここで制限時間を変更できます
    countdown_delay(0),
    countdown_after_timeup(0),   // タイムアップ後のカウントダウン時間 
    gameState(eGameState::ePlaying) // ゲーム状態の初期化
{
    event_line = new EventLine();
    n_and_p_black = new NeedleAndPatient(event_line, 0);
    n_and_p_gray = new NeedleAndPatient(event_line, 1);
    back_column = new Column;
    patient_count = 0;

    //インゲーム画像
    InGameImage = LoadGraph("Resource/Image/InGame/InGame.png");
    End = LoadGraph("Resource/Image/InGame/Finish.png");
    Start = LoadGraph("Resource/Image/InGame/Start.png");

    //カウントダウン用数字画像
    for (int i = 0; i < 10; i++) {
        numberImage[i] = LoadGraph(("Resource/Image/InGame/Number/" + std::to_string(i) + ".png").c_str());
    }
}

InGameScene::~InGameScene()
{
    // 各オブジェクトの解放
    delete event_line;
    delete n_and_p_black;
    delete n_and_p_gray;
    delete score; 
    delete back_column;
}

void InGameScene::Initialize()
{
    score->Initialize();              // スコアの初期化
    previousTime = GetNowCount();     // 前回の時間を初期化
    countdown_after_timeup = 5;       //終了時の時間
    gameState = eGameState::ePlaying; // ゲーム状態をプレイ中に初期化
    patient_count = 0;
    countdown_delay = 3;             // START時の遅延を設定
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
        if (countdown_delay >= 0) {
            if (elapsedTime >= MILLISECONDS_PER_SECOND) {
                countdown_delay--;
                previousTime = currentTime;
            }
        }
        else{
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
        //score->Update();
        back_column->AnimUpdate(true);

        //スコアを加算してもよかったら
        if (CheckAddScoreNAndP() == true)
        {
            score->AddScore(GetRedLine(), event_line->GetLineStopY());
            patient_count++;
        }
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
    back_column->Draw();
    event_line->Draw();
    n_and_p_black->Draw();
    n_and_p_gray->Draw();

    score->Draw();

    if (gameState == eGameState::ePlaying) {
        if (countdown_delay > 0) {
            DrawRotaGraph(330, 240,2,0, numberImage[countdown_delay], TRUE); //スタート時の場合
        }
        else if (countdown_delay == 0)
        {
            DrawRotaGraph(330, 240, 2, 0,Start, TRUE); //スタート時の場合
        }
        else {
            DrawGraph(10, 50, numberImage[(time / 10) % 10], TRUE); // 十の位を表示
            DrawGraph(40, 50, numberImage[time%10], TRUE); // 1の位を表示
        }
    }
    else if (gameState == eGameState::eTimeUp) {
        DrawRotaGraph(330, 240, 2, 0, End, TRUE);// タイムアップの場合
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
        //AnimUpdateをgraychangeへ
        back_column->SetGray();
    }

    if (n_and_p_gray->CheckNextStart())
    {
        n_and_p_black->SetStart();
        back_column->SetBlack();
    }

    if (n_and_p_black->CheckChangeColumn())
    {
        //AnimUpdateをgraychangeへ
        back_column->SetGray();
    }

    if (n_and_p_gray->CheckChangeColumn())
    {
        back_column->SetBlack();
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
