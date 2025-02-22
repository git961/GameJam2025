#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Object/EventLine.h"
#include "../../Object/NeedleAndPatient.h"
#include "DxLib.h"

// 1秒あたりのミリ秒数
const int MILLISECONDS_PER_SECOND = 1000;


InGameScene::InGameScene() : 
time(10),					// ここで制限時間を変更できます
countdown_after_timeup(3),  // タイムアップ後のカウントダウン時間 
time_up_flag(false)			// タイムアップフラグ
{
	event_line = new EventLine();
	n_and_p_black = new NeedleAndPatient(event_line,0);
	n_and_p_gray = new NeedleAndPatient(event_line,1);
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	score->Initialize();
	previousTime = GetNowCount(); // 前回の時間を初期化
	time_up_flag = false;		  // タイムアップフラグを初期化
	countdown_after_timeup = 3;   // カウントダウン初期化
}

eSceneType InGameScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	//{
	//	return eSceneType::eResult;
	//}

	 // 現在の時間を取得
	unsigned int currentTime = GetNowCount();

	// 前回のフレームからの経過時間を計算
	unsigned int elapsedTime = currentTime - previousTime;

	if (!time_up_flag) {


		// 1秒以上経過した場合
		if (elapsedTime >= MILLISECONDS_PER_SECOND)// 1秒以上経過した場合
		{
			time--;						// 残り時間を減らす
			previousTime = currentTime; // 前回の時間を更新

			if (time <= 0)// タイムアップ
			{
				time = 0; // 0で止める


				time_up_flag = true; // タイムアップフラグを立てる
				previousTime = currentTime; // カウントダウン開始時間を記録
			}
		}
	}
	// タイムアップ後
	else {
		if (elapsedTime >= MILLISECONDS_PER_SECOND) {
			countdown_after_timeup--; // カウントダウンを減らす
			previousTime = currentTime;

			if (countdown_after_timeup <= 0) {
				return eSceneType::eResult; // リザルト画面に移行
			}
		}
	}
	//イベントライン更新
	event_line->Update();
	//注射針と患者の更新
	n_and_p_black->Update();
	n_and_p_gray->Update();
	score->Update();
	Start_NAndP();
	return __super::Update();
}

void InGameScene::Draw() const
{
	__super::Draw();
	DrawString(10, 10, "InGame\n", GetColor(255, 255, 255));
	DrawString(10, 26, "B:Result", GetColor(255, 255, 255));
	
	event_line->Draw();
	n_and_p_black->Draw();
	n_and_p_gray->Draw();

	if (!time_up_flag) {
		DrawFormatString(10, 50, GetColor(255, 255, 255), "残り時間 : %d", time); // カウントダウンを描画
	}
	else {
		DrawFormatString(10, 50, GetColor(255, 255, 255), "End", countdown_after_timeup); // カウントダウン終了後の描画
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
	if (n_and_p_black->IsRetrunY() == true)
	{
		return n_and_p_black->GetStopY();
	}

	if (n_and_p_gray->IsRetrunY() == true)
	{
		return n_and_p_gray->GetStopY();
	}

	return 0;
}

void InGameScene::Start_NAndP()
{
	if (n_and_p_black->CheckNextStart() == true)
	{
		n_and_p_gray->SetStart();
	}

	if (n_and_p_gray->CheckNextStart() == true)
	{
		n_and_p_black->SetStart();
	}
}
