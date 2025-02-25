#include "HelpScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"

void HelpScene::Initialize()
{
	HelpImage= LoadGraph("Resource/Image/Title/HelpImage.png");
	BGM = LoadSoundMem("Resource/Sounds/BGM/TitleBGM.mp3");
	SE = LoadSoundMem("Resource/Sounds/SE/MV.mp3");
}

eSceneType HelpScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (CheckSoundMem(BGM) == 0)
	{
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, FALSE);
	}

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
		PlaySoundMem(SE, DX_PLAYTYPE_BACK, TRUE); 
		return eSceneType::eTitle;
	}
	

	return GetNowSceneType();
}

void HelpScene::Draw() const
{
	DrawExtendGraph(0, 0, 640,480,HelpImage, TRUE);
}

void HelpScene::Finalize()
{
	StopSoundMem(BGM); 
	if (background_image != NULL)
	{
		DeleteGraph(background_image);
	}
}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
