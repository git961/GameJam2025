#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"

InGameScene::InGameScene()
	: spawn_time_count(0)
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
}

eSceneType InGameScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(PAD_INPUT_B) == eInputState::ePress)
	{
		return eSceneType::eResult;
	}


	return __super::Update();
}

void InGameScene::Draw() const
{

	__super::Draw();
	//DrawString(10, 10, "インゲーム画面です\n", GetColor(255, 255, 255));
	DrawString(10, 10, "InGame\n", GetColor(255, 255, 255));
	//DrawString(10, 26, "Z:リザルト\nX:タイトル\nに遷移します", GetColor(255, 255, 255));
	DrawString(10, 26, "Z:Result", GetColor(255, 255, 255));
}

void InGameScene::Finalize()
{
	__super::Finalize();
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
