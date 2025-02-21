#pragma once
#include "../Utility/Geometry.h"

class EventLine
{
private:
	Vector2D location;//イベントラインの座標
	float stop_line_up;//イベントラインが上に上がる限界値
	float stop_line_bottom;//イベントラインが下に下がる限界値

	int stop_location_y;//イベントラインの止まったｙを入れる

	bool is_moving_up;//上に移動するか
	bool is_stop;//動きを止めるか

public:
	EventLine();
	~EventLine();
	void Update();
	void Draw()const;

	//ラインが止まったｙ座標を返す
	int GetLineStopY() { return stop_location_y; }
	//動きが止まったかを返す
	bool CheckStop();
};