#include "HelpScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"

void HelpScene::Initialize()
{
	HelpImage= LoadGraph("Resource/Image/Title/HelpImage.png");
}

eSceneType HelpScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
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
	if (background_image != NULL)
	{
		DeleteGraph(background_image);
	}
}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}
