#pragma once
#include "../Utility/Geometry.h"
#include <vector>

enum class State{
	wait,//待機状態
	come_out,//患者が出て針が降ってくる状態
	eventline_move,//イベントラインが止まるのを待つ状態
	injection,//注射する
	go_out,//右へ移動する
	finish,//終了状態
};

enum class Face
{
	cross,//×の表情
	very_tired,
	tired,
	perfect,
	fine,
	very_fine
};

class NeedleAndPatient
{
private:
	class EventLine *event_line;
	State state;//注射針と患者の動きを区切りごとに分ける用
	int stop_y;//バーをストップさせる高さ
	Vector2D needle_pos;//注射針の座標
	Vector2D patient_pos;//患者の座標
	Vector2D patient_face_pos;//患者表情の座標
	std::vector<int> needle_image;//注射針の画像
	std::vector<int> patient_image;//患者の画像
	std::vector<int> patient_face;//患者の表情画像
	double p_size;//患者画像のサイズ
	std::vector<int> column;//仮の行列
	Vector2D liquid_pos;//液体の座標
	float liquid_size;//液体のサイズ変えるよう
	std::vector<int> liquid_image;//液体の画像
	std::vector<int> stop_bar_image;//停止ラインの画像
	int patient_sum;//患者の健康具合
	int el_scaled_y;//イベントラインの数値を100にしたものを代入
	int face_alpha;//表情の透過
	
	bool is_next_start;//次のオブジェクトをスタートしていいか

	bool is_black;//黒くするか

	float angle;//cosin計算用
	Vector2D bubble;//泡の座標
	Vector2D bubble2;
	
	 Face face_state;//表情を入れる
	 int timer;//左右に患者を揺らす用

	 Vector2D effect_pos;//エフェクトの座標：左に飛ばす
	 Vector2D effect_pos2;//エフェクトの座標：右に飛ばす
	 Vector2D effect_size;//エフェクトボックスのサイズ
	 float vel;//初速を入れる
	 float acc;//重力加速

	 int count_sum;

	 int green_num;//緑色を加算する用
	 int original_color;//元の色を保管する変数
	 bool is_add_score;//スコアを加算するか

public:
	NeedleAndPatient(class EventLine *set_class,int set_num);
	~NeedleAndPatient();
	void Initialize();//初期化
	void Update();
	void Draw()const;

	//ストップさせる高さのｙ座標を返す
	int GetStopY() { return stop_y; }
	//次のオブジェクトを生成していいかx
	bool CheckNextStart() { return is_next_start; }

	bool CheckAddScore() { return is_add_score; }

	//y座標を返しても良いか
	bool IsRetrunY();
	//スタートさせる
	void SetStart() { state = State::come_out; }

private:
	void EffectUpdate();//エフェクトの更新
	void EffectDraw()const;//エフェクトの表示

};