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
	BGM = LoadSoundMem("Resource/Sounds/BGM/TitleBGM.mp3");
	SE1 = LoadSoundMem("Resource/Sounds/SE/Decide.mp3");
	SE2 = LoadSoundMem("Resource/Sounds/SE/MV.mp3");
	end_img= LoadGraph("Resource/Image/Title/EndImage.png");
	is_result = false;
	end_frame_cnt = 0;
	end_count = 0;
}



eSceneType TitleScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (is_result == false) {
		if (CheckSoundMem(BGM) == 0)
		{
			PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, FALSE);
		}

		//Bボタンが押されたら
		if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
		{
			PlaySoundMem(SE2, DX_PLAYTYPE_BACK, TRUE);

			switch (cursor_number)
			{
			case 0:
				//インゲーム画面に移動
				return eSceneType::eInGame;
			case 1:

				return eSceneType::eHelp;
			case 2:
				//return eSceneType::eEnd;
				is_result = true;
			default:
				break;
			}
		}
		SelectCursor();
	}
	else
	{
		if (end_frame_cnt++ > 60)
		{
			end_frame_cnt = 0;
			end_count++;
		}
		if (end_count > 5)
		{
			return eSceneType::eEnd;

		}

	}
	
	return GetNowSceneType();	
}

void TitleScene::Draw() const
{
	if (is_result == false) {

		DrawGraph(0, 0, Title_image, TRUE);
		DrawExtendGraph(0, 0, 640, 480, Title_image, TRUE);

		DrawGraph(380, cursor_y, arrow_image, TRUE);
	}
	else
	{
		DrawGraph(0, 0, end_img, TRUE);
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
			PlaySoundMem(SE1, DX_PLAYTYPE_BACK, TRUE);
		
	}
	if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::ePress)
	{
		cursor_number++;
		cursor_number = cursor_number % 3;

		PlaySoundMem(SE1, DX_PLAYTYPE_BACK,TRUE);
	}

	cursor_y = 160+ (cursor_number * 80);

	
}



void TitleScene::Finalize()
{
	StopSoundMem(BGM);
	if (background_image != NULL)
	{
		DeleteGraph(background_image);
	}
}


eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
