#include "ResultScene.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//zを押したらタイトルへ戻る
	if (pad_input->GetKeyInputState(PAD_INPUT_B) == eInputState::ePress)
	{
		return eSceneType::eTitle;
	}

	return GetNowSceneType();
}

void ResultScene::Draw() const
{	
	DrawString(10, 10, "Result\n", GetColor(255, 255, 255));
	DrawString(10, 26, "Z:Title", GetColor(255, 255, 255));

}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	//自分のsecenetypeを返す
	return eSceneType::eResult;
}
