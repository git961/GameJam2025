#pragma once

#include "../Utility/Geometry.h"
//#include "../Object/GameObject.h"
#include <vector>


enum class eSceneType
{
	eTitle,
	eInGame,
	eResult,
	eHelp,
	eEnd,
};

class SceneBase
{
protected:
	//std::vector<GameObject*> objects;
	int background_image;

public:

	SceneBase();
	virtual ~SceneBase();

public:
	virtual void Initialize();
	virtual eSceneType Update();
	virtual void Draw() const;
	virtual void Finalize();

public:
	virtual eSceneType GetNowSceneType() const = 0;

protected:

	//template <class T>
	//T* CreateObject(const Vector2D& location)
	//{
	//	T* new_instance = new T();

	//	GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

	//	if (new_object == nullptr)
	//	{
	//		delete new_instance;
	//		throw("ゲームオブジェクトが生成できませんでした\n");
	//	}

	//	new_object->SetLocation(location);

	//	new_object->Initialize();

	//	objects.push_back(new_object);

	//	return new_instance;
	//}

	//void DestroyObject(GameObject* target);
};

