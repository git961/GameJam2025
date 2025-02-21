#include "TitleScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"



void TitleScene::Initialize()
{
	cursor_number = 0;
	cursor_y = 360;
	arrow_image = LoadGraph("Resource/Images/arrow.png");

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
	SelectCursor();



	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawString(10, 10, "Title\n", GetColor(255, 255, 255));

	switch (cursor_number)
	{
	case 0:
		//インゲーム画面に移動
		DrawString(10, 26, "InGame", GetColor(255, 255, 255));
		break;
	case 1:
		//ヘルプ
		DrawString(10, 26, "A:Help", GetColor(255, 255, 255));
		break;
	case 2:
		DrawString(10, 26, "X:GameEnd", GetColor(255, 255, 255));
		break;
	default:
		break;
	}
}


void TitleScene::SelectCursor()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_UP) == eInputState::ePress)
	{
		cursor_number--;
		if (cursor_number < 0)
		{
			cursor_number = 2;
		}
	}
	if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number = cursor_number % 3;
	}

	cursor_y = 360 + (cursor_number * 85);
	
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
