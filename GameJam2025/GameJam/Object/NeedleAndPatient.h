#pragma once
#include "../Utility/Geometry.h"
#include <vector>

enum class State{
	come_out,//患者が出て針が降ってくる状態
	eventline_move,//イベントラインが止まるのを待つ状態
	injection,//注射する
	go_out,//右へ移動する
};

class NeedleAndPatient
{
private:
	class EventLine *event_line;
	State state;//注射針と患者の動きを区切りごとに分ける用
	int stop_y;//バーをストップさせる高さ
	Vector2D needle_pos;//注射針の座標
	Vector2D patient_pos;//患者の座標
	std::vector<int> needle_image;//注射針の画像
	std::vector<int> patient;//患者の画像
	double p_size;//患者画像のサイズ
	std::vector<int> column;//仮
	Vector2D liquid_pos;//液体の座標
	float liquid_size;//液体のサイズ変えるよう

	int patient_sum;//患者の健康具合
	int el_sum;//イベントラインの数値

public:
	NeedleAndPatient(class EventLine *set_class);
	~NeedleAndPatient();
	void Initialize();//初期化
	void Update();
	void Draw()const;

	//ストップさせる高さのｙ座標を返す
	int GetStopY() { return stop_y; }
};

