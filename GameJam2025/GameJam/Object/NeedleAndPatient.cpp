#include "NeedleAndPatient.h"
#include "EventLine.h"
#include "DxLib.h"
#include "../Utility/ResourceManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

NeedleAndPatient::NeedleAndPatient(EventLine *set_class,int set_num)
{
	if (set_num == 0)
	{
		//黒の場合
		//中央へ出てくる時の状態にする
		state = State::come_out;
		is_black = true;
		original_color = 73;
	}
	else
	{
		//灰色の場合
		//待機状態にする
		state = State::wait;
		is_black = false;
		original_color = 117;
	}
	event_line = set_class;
	Initialize();
	//画像を読み込む
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Image/InGame/syring.png");
	needle_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/patient.png");
	patient_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/column.png");
	column.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/liquid.png");
	liquid_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/stop_bar.png");
	stop_bar_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/face.png", 6, 6, 1, 64, 42);
	for (int i = 0; i < 6; i++)
	{
		patient_face.push_back(tmp[i]);
	}
}

NeedleAndPatient::~NeedleAndPatient()
{
}

void NeedleAndPatient::Initialize()
{
	//最大値と最小値の間の数値をランダムで取得
	int max_y = 250;
	int min_y = 10;
	stop_y = min_y + (int)(rand() * (max_y - min_y + 1.0) / (1.0 + RAND_MAX));
	//stop_y = 10;
	el_scaled_y = 0;

	//240を100の範囲に変換
	int num = (int)round(stop_y * (100.0 / max_y));
	//stop_yを足したらちょうど100程になるように
	patient_sum = 100 - num;

	needle_pos.x = 320.0f;
	needle_pos.y = -270.0f;
	//患者初期位置とサイズ
	patient_pos.x =230.0f;
	patient_pos.y = 400.0f;
	p_size = 2.0;

	//液体の座標
	liquid_pos.x = 250.0f;
	liquid_pos.y = 10.0f;
	liquid_size = 0.0f;

	//泡の座標
	bubble.x=320.0f;
	bubble.y = 240.0f;
	bubble2 = bubble;
	angle = 0.0f;
	//透明状態に
	face_alpha = 0;

	is_next_start = false;

	//表情を表示
	if (patient_sum <= 50)
	{
		//very tired 50以下
		face_state = Face::very_tired;
	}
	else
	{
		//tired 95以下
		face_state = Face::tired;
	}
	timer = 0;

	//エフェクトの座標初期化
	effect_pos = 0.0f;
	effect_pos2 = 0.0f;
	effect_size = 5.0f;
	vel = -10;
	acc = 1;

	count_sum = 0;
	green_num = original_color;
}

void NeedleAndPatient::Update()
{
	switch (state)
	{
	case State::wait:
		break;
	case State::come_out:
		//中心まで患者が出てくる
		if (patient_pos.x < 320.0f)
		{
			patient_pos.x += 5;
		}
		if (patient_pos.y < 420)
		{
			patient_pos.y += 5;
		}
		if (p_size < 2.8)
		{
			p_size += 0.1;
		}

		//注射針が下に落ちてくる
		needle_pos.y += 7.0f;
		if (needle_pos.y > 145)
		{
			//下に落ちきったらy座標を入れてstateを変更する
			needle_pos.y = 145.0f;
			state = State::eventline_move;
			face_state = Face::cross;

			//エフェクトの座標をセット
			effect_pos.x = patient_pos.x;
			effect_pos.y = patient_pos.y-140.0f;
			effect_pos2.x = patient_pos.x;
			effect_pos2.y = patient_pos.y-140.0f;

			//event_line動かす
			event_line->Start();
		}
		break;
	case State::eventline_move:

		if (timer++<10)
		{
			//偶数かチェック : 偶数だったら＋奇数だったらマイナス
			if (timer % 2 == 0)
			{
				patient_pos.x += 4.0f;
			}
			else {
				patient_pos.x -= 4.0f;

			}
		}

		if (event_line->CheckStop() == true)
		{
			//250を100の範囲に変換
			el_scaled_y = (int)round(event_line->GetLineStopY() * (100.0 / 250.0));
			patient_sum += el_scaled_y;
			//event_lineが止まったら次の状態へ
			state = State::injection;
		}
		else
		{
			//cos動き
			angle += 2;
			bubble.y -= 2;
			if (bubble.y < 10)
			{
				bubble.y = 240.0f;
			}
			bubble2.y -= 1;
			if (bubble2.y < 10)
			{
				bubble2.y = 240.0f;
			}

			if (angle > 360)
			{
				angle = 0.0f;
			}
			float radian = angle * (float)M_PI / 180.0f;
			float result = cosf(radian);
			bubble.x += result;
			bubble2.x -= result;
		}
		break;
	case State::injection://液体の注射
		//表情を変化させる
		green_num ++;
		timer++;
		//偶数かチェック : 偶数だったら＋奇数だったらマイナス
		if (timer % 2 == 0)
		{
			patient_pos.x += 4.0f;
		}
		else {
			patient_pos.x -= 4.0f;

		}

		//表情の変化用
		if (count_sum <= patient_sum)
		{
			count_sum += 2;
		}
		else
		{
			count_sum = patient_sum;
		}

		//表情を表示
		if (count_sum <= 50)
		{
			//very tired 50以下
			face_state = Face::very_tired;
		}
		else if (count_sum <= 95)
		{
			//tired 90以下
			face_state = Face::tired;
		}
		else if (count_sum >= 150)
		{
			//very fine 150以上
			face_state = Face::very_fine;
		}
		else if (count_sum >= 105)
		{
			//fine? 105以上
			face_state = Face::fine;
		}

		if (liquid_size <= event_line->GetLineStopY())
		{
			liquid_size += 2;
		}

		//液が下がり切って、表情が変わり切るまで待つ
		if (event_line->GetLineStopY() <= liquid_size &&count_sum>=patient_sum)
		{
			liquid_size = (float)event_line->GetLineStopY();
			//イベントラインを止める
			event_line->Stop();
			count_sum = patient_sum;

			//patient_sumが94以上104以下ならperfectに入れる
			if (patient_sum >= 96 && patient_sum <= 104)
			{
				//perfect 100
				face_state = Face::perfect;
			}

			state = State::go_out;
		}

		break;
	case State::go_out:
		//注射が終わったら右へ移動
		needle_pos.x += 5;
		patient_pos.x += 5;
		liquid_pos.x += 5;

		if (needle_pos.x > 630)
		{
			is_next_start = true;
		}

		//wait状態へ
		if (needle_pos.x > 700)
		{
			is_next_start = false;
			state = State::finish;
		}
		break;
	case State::finish:
		Initialize();
		state = State::wait;
		break;
	default:
		break;
	}

	if (state == State::eventline_move || state == State::injection)
	{
		EffectUpdate();
	}
}

void NeedleAndPatient::Draw() const
{
	//wait状態じゃなかったら表示する
	if (state != State::wait)
	{
		//後ろの列の仮表示
		DrawRotaGraph(120, 400, 1.5, 0, column[0], TRUE);

		//液体の表示
		if (state == State::come_out)
		{
			//20.0fはneedle_imageとの画像の中心の差
			DrawRotaGraphF(needle_pos.x, needle_pos.y - 20.0f, 1, 0, liquid_image[0], TRUE);
		}
		else
		{
			DrawExtendGraphF(liquid_pos.x,  liquid_size, liquid_pos.x + 140.0f, liquid_pos.y + 240.0f, liquid_image[0],TRUE);
		}
		if (state == State::eventline_move)
		{
			//泡表示
			DrawCircle((int)bubble.x, (int)bubble.y, 5, 0xffffff, TRUE);
			DrawCircle((int)bubble2.x, (int)bubble2.y, 3, 0xffffff, TRUE);
		}

		//液体隠す用
		DrawBoxAA(needle_pos.x-70.0f, 0.0f, needle_pos.x+70.0f, 10.0f, 0x999999, TRUE);
		//注射器の画像表示
		DrawRotaGraph((int)needle_pos.x, (int)needle_pos.y, 1, 0, needle_image[0], TRUE);


		//SetDrawBrightで色の変更
		if (is_black == true)
		{
			SetDrawBright(73, green_num, 73);
		}
		else {
			SetDrawBright(117, green_num, 117);
		}
		//患者の表示
		DrawRotaGraphF(patient_pos.x, patient_pos.y, p_size, 0, patient_image[0], TRUE);
		//255,255,255でSetDrawBrightで変えた色を戻す
		SetDrawBright(255,255,255);



		//患者の表情表示
		DrawRotaGraphF(patient_pos.x, patient_pos.y - 70.0f, p_size, 0, patient_face[(int)face_state], TRUE);

		//描画ブレンドモードをアルファブレンドにする
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, face_alpha);
		
		if (patient_sum <= 50)
		{
			//very tired 50以下
			DrawFormatStringF(patient_pos.x, patient_pos.y, 0x000000, "verytired");
		}
		else if (patient_sum <= 95)
		{
			//tired 95以下
			DrawFormatStringF(patient_pos.x, patient_pos.y, 0x000000, "tired");
		}
		else if (patient_sum >= 150)
		{
			//very fine 150以上
			DrawFormatStringF(patient_pos.x, patient_pos.y, 0x000000, "veryfine");
		}
		else if (patient_sum >= 105)
		{
			//fine? 105以上
			DrawFormatStringF(patient_pos.x, patient_pos.y, 0x000000, "fine?");
		}
		else {
			//good_nomal 100
			DrawFormatStringF(patient_pos.x, patient_pos.y, 0x000000, "good");
		}
		
		//アルファブレンドを止める
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, face_alpha);

		//DrawFormatString(100, 40, 0x000000, "el_sum:%d", el_scaled_y);
		DrawFormatString(100, 60, 0x000000, "patient_sum:%d", patient_sum);
		//DrawFormatString(100, 80, 0x000000, "liquid_y:%d", (int)liquid_pos.y + (int)liquid_size);
		DrawFormatString(100, 100, 0x000000, "stop_y:%d", stop_y);
		DrawFormatString(100, 120, 0x000000, "eventline_y:%d", event_line->GetLineStopY());
		//DrawFormatString(100, 120, 0x000000, "needle_x:%f", needle_pos.x);
		//DrawFormatString(100, 120, 0x000000, "liquid_size:%f", liquid_size);

		EffectDraw();

		//止めるとこの表示↓
		if (needle_pos.y >= 145)
		{
			DrawRotaGraphF(needle_pos.x, (float)stop_y, 1, 0, stop_bar_image[0], TRUE);
		}
	}
}

bool NeedleAndPatient::IsRetrunY()
{
	//wait,finish状態じゃなかったらtrueを返す
	if (state != State::wait && state!=State::finish )
	{
		return true;
	}
	return false;
}

void NeedleAndPatient::EffectUpdate()
{
	if (effect_pos.y < 800)
	{
		//velにaccを追加
		vel += acc;
		effect_pos.y += vel;
		effect_pos2.y += vel;

		effect_pos.x += 4.0f;
		effect_pos2.x -= 4.0f;
	}
}

void NeedleAndPatient::EffectDraw() const
{
	float shift = 1.0f;


	float frame_size_x = effect_pos.x + effect_size.x + shift;
	float frame_size_y = effect_pos.y + effect_size.y + shift;

	float frame_size_x2 = effect_pos2.x + effect_size.x + shift;
	float frame_size_y2 = effect_pos2.y + effect_size.y + shift;

	//枠部分
	DrawBoxAA(effect_pos.x - shift, effect_pos.y - shift, frame_size_x, frame_size_y, 0xffffff, TRUE);
	DrawBoxAA(effect_pos.x - shift-4.0f, effect_pos.y - shift - 6.0f, frame_size_x-4.0f, frame_size_y - 6.0f, 0xffffff, TRUE);

	DrawBoxAA(effect_pos2.x - shift, effect_pos2.y - shift, frame_size_x2, frame_size_y2, 0xffffff, TRUE);
	DrawBoxAA(effect_pos2.x - shift-7.0f, effect_pos2.y - shift - 6.0f, frame_size_x2-7.0f, frame_size_y2 - 6.0f, 0xffffff, TRUE);


	float box_size_x = effect_pos.x + effect_size.x;
	float box_size_y = effect_pos.y + effect_size.y;

	float box_size_x2 = effect_pos2.x + effect_size.x;
	float box_size_y2 = effect_pos2.y + effect_size.y;
	//四角部分
	DrawBoxAA(effect_pos.x, effect_pos.y, box_size_x, box_size_y, 0x68ff00, TRUE);
	DrawBoxAA(effect_pos.x-4.0f , effect_pos.y - 6.0f, box_size_x-4.0f, box_size_y - 6.0f, 0x68ff00, TRUE);

	DrawBoxAA(effect_pos2.x, effect_pos2.y , box_size_x2, box_size_y2, 0x68ff00, TRUE);
	DrawBoxAA(effect_pos2.x-7.0f, effect_pos2.y - 6.0f, box_size_x2-7.0f, box_size_y2 - 6.0f, 0x68ff00, TRUE);

}
