#include "TitleScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"


void TitleScene::Initialize()
{
	cursor_number = 0;
}


eSceneType TitleScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Bボタンが押されたら
	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
		switch (cursor_number)
		{
		case 0:
			//インゲーム画面に移動
			return eSceneType::eInGame;
		case 1:
			//ヘルプ
			return eSceneType::eHelp;
		case 2:
			return eSceneType::eEnd;

		default:
			break;
		}
	}



	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawString(10, 10, "Title\n", GetColor(255, 255, 255));
	DrawString(10, 26, "B:InGame\nA:Help\nX:GameEnd\n", GetColor(255, 255, 255));
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
