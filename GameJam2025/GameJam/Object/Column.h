#pragma once
#include "../Utility/Geometry.h"
#include <vector>

enum class AnimState {
	black,
	change_gray,
	gray,
	change_black
};

class Column
{
private:
	AnimState anim_state;
	Vector2D location;//座標
	std::vector<int> column_img;//動く後ろの列
	double img_size;//画像サイズ
	int img_num;//画像表示番号 Max_11まで
	int anim_cnt;
	int frame_cnt;
	int SE1;

public:
	Column();
	~Column();
	void Initialize();//初期化
	void AnimUpdate(bool is_black);
	void Draw()const;

	void SetGray() {
		if (anim_state == AnimState::black) {
			anim_state = AnimState::change_gray;
			img_num = 4;
		}
	}
	void SetBlack() {
		if (anim_state == AnimState::gray) {
			anim_state = AnimState::change_black;
			img_num = 10;
		}
	}
};

