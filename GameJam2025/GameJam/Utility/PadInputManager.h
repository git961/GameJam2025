#pragma once
#include "Enum.h"
#include "Geometry.h"
#include "DxLib.h"
#define PAD_KEYCODE_MAX	(16)


class PadInputManager
{
private:
	//静的メンバ変数の宣言
//インスタンスを生成しなくても呼び出すことができる
	static PadInputManager* instance;

	XINPUT_STATE now_key;
	XINPUT_STATE old_key;


private:
	//GetInstance以外でnewさせない為にコンストラクタとデストラクタをprivateに

	PadInputManager() = default;
	//コピーコンストラクタを明確に定義
	//コンストラクタの引数に同名クラスの参照を指定するのがコピーコンストラクタ
	PadInputManager(const PadInputManager&) = delete;//= deleteで使用不可にする
	//代入演算子
	PadInputManager& operator = (const PadInputManager&) = delete;//= deleteで使用不可にする

public:
	~PadInputManager() = default;

public:
	//静的メンバ関数 クラスそのものがもつ関数
	static PadInputManager* GetInstance();
	static void DeleteInstance();

public:
	void Update();

public:
	//keycodeの値から判別してeInputStateを返す
	eInputState GetKeyInputState(int keycode);
	//スティックの値を返す
	Vector2D GetJoyStickRight();
	Vector2D GetJoyStickLeft();

private:
	bool CheckKeycodeRange(int keycode);


};

