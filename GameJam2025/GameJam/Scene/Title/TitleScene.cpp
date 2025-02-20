#include "TitleScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"

void TitleScene::Initialize()
{
}

eSceneType TitleScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
		return eSceneType::eInGame;
	}
	if (pad_input->GetKeyInputState(PAD_INPUT_A) == eInputState::ePress)
	{
		return eSceneType::eHelp;
	}
	if (pad_input->GetKeyInputState(PAD_INPUT_X) == eInputState::ePress)
	{
		return eSceneType::eEnd;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	//DrawString(10, 10, "タイトル画面です\n", GetColor(255, 255, 255));
	DrawString(10, 10, "Title\n", GetColor(255, 255, 255));
	//DrawString(10, 26, "Z:インゲーム\nX:ヘルプ\nC:ゲーム終了\nに遷移します", GetColor(255, 255, 255));
	DrawString(10, 26, "Z:InGame\nX:Help\nC:GameEnd\nに遷移します", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
	if (background_image != NULL)
	{
		DeleteGraph(background_image);
	}
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
