#include "PadInputManager.h"
//静的メンバ変数を定義と初期化
PadInputManager* PadInputManager::instance = nullptr;

PadInputManager* PadInputManager::GetInstance()
{
	//呼び出されたのが初回だったらインスタンスを生成
	if (instance == nullptr)
	{
		instance = new PadInputManager();
	}

	//実体を返す
	return instance;
}

void PadInputManager::DeleteInstance()
{
	//実体が生成されていたらdeleteする
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void PadInputManager::Update()
{
	old_key = now_key;
	//入力状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &now_key);

}

eInputState PadInputManager::GetKeyInputState(int keycode)
{
	//キーコードの範囲内かチェック
	if (CheckKeycodeRange(keycode))
	{
		if (old_key.Buttons[keycode] == TRUE)
		{
			if (now_key.Buttons[keycode] == TRUE)
			{
				return eInputState::eHeld;
			}
			else
			{
				return eInputState::eRelease;
			}
		}
		else
		{
			if (now_key.Buttons[keycode] == TRUE)
			{
				return eInputState::ePress;
			}
			else
			{
				return eInputState::eNone;
			}
		}
	}
	return eInputState::eNone;

}

Vector2D PadInputManager::GetJoyStickRight()
{
	Vector2D right_location(now_key.ThumbRX,now_key.ThumbRY);
	return right_location;
}

Vector2D PadInputManager::GetJoyStickLeft()
{
	Vector2D left_location(now_key.ThumbLX, now_key.ThumbLY);
	return left_location;
}

bool PadInputManager::CheckKeycodeRange(int keycode)
{
	return (0 <= keycode && keycode < PAD_KEYCODE_MAX);
}
