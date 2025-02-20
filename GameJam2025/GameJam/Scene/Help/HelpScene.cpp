#include "HelpScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"

void HelpScene::Initialize()
{
}

eSceneType HelpScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(KEY_INPUT_X) == eInputState::ePress)
	{
		return eSceneType::eTitle;
	}
	return GetNowSceneType();
}

void HelpScene::Draw() const
{
	DrawString(10, 10, "HelpScene\n", GetColor(255, 255, 255));
	//DrawString(10, 26, "Z:インゲーム\nX:タイトル\nに遷移します", GetColor(255, 255, 255));
	DrawString(10, 26, "X:Title", GetColor(255, 255, 255));
}

void HelpScene::Finalize()
{
	if (background_image != NULL)
	{
		DeleteGraph(background_image);
	}
}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
