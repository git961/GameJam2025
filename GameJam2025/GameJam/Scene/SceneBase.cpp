#include "SceneBase.h"
#include "DxLib.h"

SceneBase::SceneBase(): background_image(NULL)
{
}

SceneBase::~SceneBase()
{
	this->Finalize();
}

//初期化処理
void SceneBase::Initialize()
{
}

eSceneType SceneBase::Update()
{
	//更新処理
	//範囲for文書き方
	//for(型　変数名 : 配列やコレクションなどの要素を持つオブジェクト)
	//オブジェクトの要素を順番にループ変数(obj)に代入してループ処理を実行する
	//for (GameObject* obj : objects)
	//{
	//	obj->Update();
	//}

	return GetNowSceneType();
}

void SceneBase::Draw() const
{
	DrawGraph(0, 0, background_image, TRUE);

	//for (GameObject* obj : objects)
	//{
	//	obj->Draw();
	//}
}

void SceneBase::Finalize()
{
	//objectsの要素が空かどうか調べる
	//if (objects.empty())
	//{
	//	return;
	//}

	//for (GameObject* obj : objects)
	//{
	//	obj->Finalize();
	//	delete obj;
	//}

	//objects.clear();
}
//
//void SceneBase::DestroyObject(GameObject* target)
//{
//}
