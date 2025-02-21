#include "InGameScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	score->Initialize();
}

eSceneType InGameScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
		return eSceneType::eResult;
	}

	score->Update();

	return __super::Update();

}

void InGameScene::Draw() const
{
	__super::Draw();
	DrawString(10, 10, "InGame\n", GetColor(255, 255, 255));
	DrawString(10, 26, "B:Result", GetColor(255, 255, 255));
}

void InGameScene::Finalize()
{
	__super::Finalize();
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
