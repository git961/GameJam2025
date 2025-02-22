#include "DxLib.h"
#include "Utility/FPS.h"
#include "Utility/PadInputManager.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"
#include <time.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)

{
	ChangeWindowMode(FALSE);

	if (DxLib_Init() == -1)

	{

		return -1;

	}
	//乱数の計算に使う元の数を変更
	srand((unsigned int)time(NULL));

	SetDrawScreen(DX_SCREEN_BACK);
	SceneManager* manager = nullptr;
	int result = 0;

	FPS fp;
	//ループ前にFPS計測を初期化
	fp.Reset_FPS();

	try
	{
		//SceneManager型の動的メモリを確保
		manager = new SceneManager;
		manager->Initialize();
		PadInputManager* pad_input = PadInputManager::GetInstance();
		while (ProcessMessage() != -1 && manager->LoopCheck())
		{
			//fps固定
			fp.FPSUpdate();

			pad_input->Update();
			ClearDrawScreen();
			manager->Update();
			ScreenFlip();

			//Backボタンを押したらゲーム終了
			if (pad_input->GetKeyInputState(XINPUT_BUTTON_BACK) == eInputState::eRelease)
			{
				break;
			}
		}
	}
	catch (std::string& error_text)
	{
		//throwで投げられた文をデバッグの出力に表示
		OutputDebugString(error_text.c_str());
		result = -1;
	}

	PadInputManager::DeleteInstance();
	ResourceManager::DeleteInstance();

	if (manager != nullptr)
	{
		manager->Finalize();
		delete manager;		//動的メモリの解放
	}

	DxLib_End();

	return 0;

}