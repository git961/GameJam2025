#pragma once
#include "SceneBase.h"

class SceneManager
{
private:
	SceneBase* current_scene;
	bool loop_flag;
public:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	void Update();
	void Finalize();

public:
	bool LoopCheck() const;

private:
	void ChangeScene(eSceneType new_scene_type);

	//ファクトリー関数
	//引数を生成したいクラスのタイプ
	SceneBase* CreateScene(eSceneType new_scene_type);
};

