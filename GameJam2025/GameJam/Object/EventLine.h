#pragma once
#include "../Utility/Geometry.h"
#include <vector>

class EventLine
{
private:
	Vector2D location;//イベントラインの座標
	float stop_line_up;//イベントラインが上に上がる限界値
	float stop_line_bottom;//イベントラインが下に下がる限界値
	float speed;//上下移動の速さ
	int stop_location_y;//イベントラインの止まったｙを入れる

	bool is_moving_up;//上に移動するか
	bool is_stop;//動きを止めるか
	bool is_start;//スタートするかどうか

	std::vector<int> triangle_img;//三角の画像
	std::vector<int> range_img;//イベントラインの動く範囲の画像

public:
	EventLine();
	~EventLine();
	void Initialize();//初期化
	void Update();
	void Draw()const;

	//ラインが止まったｙ座標を返す
	int GetLineStopY();
	//動きが止まったかを返す
	bool CheckStop();
	//is_startをtrueにする
	void Start() { is_start = true; }
	//イベントラインを初期化する
	void Stop();
};