#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Object/EventLine.h"
#include "../../Object/NeedleAndPatient.h"
#include "DxLib.h"

// 1秒あたりのミリ秒数
const int MILLISECONDS_PER_SECOND = 1000;


InGameScene::InGameScene() : time(60)// ここで制限時間を変更できます
{
	event_line = new EventLine();
	n_and_p = new NeedleAndPatient(event_line);
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	score->Initialize();
	previousTime = GetNowCount(); // 前回の時間を初期化
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

	// 1秒以上経過した場合
	if (elapsedTime >= MILLISECONDS_PER_SECOND)// 1秒以上経過した場合
	{
		time--;// 残り時間を減らす
		previousTime = currentTime; // 前回の時間を更新

		if (time <= 0)// タイムアップ
		{
			time = 0; // 0で止める
			// タイムアップ時の処理 (例: return eSceneType::eResult;)
			return eSceneType::eResult;
		}
	}

	//イベントライン更新
	event_line->Update();
	//注射針と患者の更新
	n_and_p->Update();
	score->Update();

	return __super::Update();

}

void InGameScene::Draw() const
{
	__super::Draw();
	DrawString(10, 10, "InGame\n", GetColor(255, 255, 255));
	DrawString(10, 26, "B:Result", GetColor(255, 255, 255));
	// カウントダウンを描画
	

	event_line->Draw();
	n_and_p->Draw();
	DrawFormatString(10, 50, GetColor(255, 255, 255), "残り時間 : %d", time);
}

void InGameScene::Finalize()
{
	__super::Finalize();
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
