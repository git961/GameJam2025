#pragma once
#include "../Utility/Geometry.h"
#include <vector>
class NeedleAndPatient
{
private:
	class EventLine *event_line;

	int stop_y;//ストップさせる高さ
	Vector2D needle_pos;//注射針の座標
	std::vector<int> needle_image;//注射針の画像
	std::vector<int> patient;//患者の画像

public:
	NeedleAndPatient(class EventLine *set_class);
	~NeedleAndPatient();
	void Initialize();//初期化
	void Update();
	void Draw()const;

	//ストップさせる高さのｙ座標を返す
	int GetStopY() { return stop_y; }
};

