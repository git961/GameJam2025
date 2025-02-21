#include "TitleScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"



void TitleScene::Initialize()
{
	cursor_number = 0;
	cursor_y = 360;
	arrow_image = LoadGraph("Resource/Image/Title/arrow.png");
	Title_image = LoadGraph("Resource/Image/Title/Title.png");

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
			
			return eSceneType::eHelp;
		case 2:
			return eSceneType::eEnd;

		default:
			break;
		}
	}
	SelectCursor();


	
	return GetNowSceneType();

	//if(arrow_image=80, arrow_image+80, arrow_image>=320)
		
}

void TitleScene::Draw() const
{
	DrawString(10, 10, "Title\n", GetColor(255, 255, 255));
	DrawGraph(0, 0, Title_image, TRUE);
	DrawExtendGraph(0, 0, 640, 480, Title_image, TRUE);

	DrawGraph(380, cursor_y, arrow_image, TRUE);


	

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

	cursor_y = 160+ (cursor_number * 80);
	
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
