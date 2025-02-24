#include "ResultScene.h"
#include "../../Utility/PadInputManager.h"
#include"../../Object/Score.h"
#include "DxLib.h"

ResultScene::ResultScene()
{
	score = new Score;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	score->Initialize();
}

eSceneType ResultScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Bを押したらタイトルへ戻る
	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
		return eSceneType::eTitle;
	}

	score->Update();

	return GetNowSceneType();
}

void ResultScene::Draw() const
{	
	DrawString(10, 10, "Result\n", GetColor(255, 255, 255));
	DrawString(10, 26, "B:Title", GetColor(255, 255, 255));

	score->Draw();
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	//自分のsecenetypeを返す
	return eSceneType::eResult;
}
