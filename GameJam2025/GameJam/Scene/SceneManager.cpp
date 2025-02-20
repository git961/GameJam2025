#include "SceneManager.h"

#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "Help/HelpScene.h"
#include "Result/ResultScene.h"

SceneManager::SceneManager()
	: current_scene(nullptr)
	,loop_flag(true)
{
}

SceneManager::~SceneManager()
{
	this->Finalize();
}

void SceneManager::Initialize()
{
	//タイトルを生成
	ChangeScene(eSceneType::eTitle);
}

void SceneManager::Update()
{
	//current_sceneのアップデートからeSceneTypeの列挙子が返ってくる
	eSceneType next_scene_type = current_scene->Update();
	current_scene->Draw();

	//次のsceneと今のsceneが同じではない場合
	//生成と破棄を行う
	if (next_scene_type != current_scene->GetNowSceneType())
	{
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Finalize()
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;//メモリの解放 インスタンスを消す
		current_scene = nullptr;//ポインタをnullptrにする 住所だけ残しても危ない為
	}
}

bool SceneManager::LoopCheck() const
{
	return loop_flag;
}


void SceneManager::ChangeScene(eSceneType new_scene_type)
{
	//今のscenetypeがeEndだったらループを止める
	if (new_scene_type == eSceneType::eEnd)
	{
		loop_flag = false;
		return;
	}

	//CreateSceneで生成したインスタンスのポインタを受け取る
	SceneBase* new_scene = CreateScene(new_scene_type);

	//CreateSceneで生成出来たかチェック
	if (new_scene == nullptr)
	{
		throw("\n新しいシーンの生成ができませんでした\n");
	}

	//今のsceneに値が入っていたら
	if (current_scene != nullptr)
	{
		//sceneの破棄
		current_scene->Finalize();
		delete current_scene;
	}

	new_scene->Initialize();
	//今のシーンにポインタを渡す
	current_scene = new_scene;
}

//ファクトリー関数
//生成したいクラスのタイプを引数で受け取る(eSceneType new_scene_type)
//戻り値でインタフェースクラス(SceneBase)のポインタを返す
SceneBase* SceneManager::CreateScene(eSceneType new_scene_type)
{
	//クラスを生成し、インスタンスを返却する
	//新しいシーンの生成
	//dynamic_castでscenebaseを引き継いでいるか確認
	switch (new_scene_type)
	{
	case eSceneType::eTitle:
		//newでメモリを確保
		//dynamic_castでSceneBaseを引き継いでいるか確認
		return  dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::eInGame:
		return  dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eHelp:
		return  dynamic_cast<SceneBase*>(new HelpScene());
	case eSceneType::eResult:
		return dynamic_cast<SceneBase*>(new ResultScene());
	case eSceneType::eEnd:
	default:
		return nullptr;
	}
}
