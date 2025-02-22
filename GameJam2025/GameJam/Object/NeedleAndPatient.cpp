#include "NeedleAndPatient.h"
#include "EventLine.h"
#include "DxLib.h"
#include "../Utility/ResourceManager.h"

NeedleAndPatient::NeedleAndPatient(EventLine *set_class)
{
	event_line = set_class;
	Initialize();
	//画像を読み込む
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Image/InGame/syring.png");
	needle_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/patient.png");
	patient.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/column.png");
	column.push_back(tmp[0]);
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
	el_sum = 0;

	//240を100の範囲に変換
	int num = round(stop_y * (100.0 / max_y));
	//stop_yを足したらちょうど100程になるように
	patient_sum = 100 - num;

	needle_pos.x = 320.0f;
	needle_pos.y = -270.0f;
	//患者初期位置とサイズ
	patient_pos.x =230.0f;
	patient_pos.y = 400.0f;
	p_size = 2.0;

	//中央へ出てくる時の状態にする
	state = State::come_out;

	//液体の座標
	liquid_pos.x = 250.0f;
	liquid_pos.y = 10.0f;
	liquid_size = 0.0f;
}

void NeedleAndPatient::Update()
{
	switch (state)
	{
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
		if (needle_pos.y < 145)
		{
			needle_pos.y += 7.0f;
		}
		else {
			//下に落ちきったらy座標を入れてstateを変更する
			needle_pos.y = 145.0f;
			state = State::eventline_move;
			//event_line動かす
			event_line->Start();
		}
		break;
	case State::eventline_move:
		if (event_line->CheckStop() == true)
		{
			//250を100の範囲に変換
			el_sum = round(event_line->GetLineStopY() * (100.0 / 250.0));
			patient_sum += el_sum;
			//event_lineが止まったら次の状態へ
			state = State::injection;
		}
		break;
	case State::injection:
		//注射
		if (event_line->GetLineStopY() > liquid_size)
		{
			liquid_size += 1;
		}
		else
		{
			liquid_size = event_line->GetLineStopY();
			//イベントラインを止める
			event_line->Stop();
			state = State::go_out;
		}

		//if (patient_sum)
		//{
		//	//patient_sum+=止めたところの数値
		//}

		break;
	case State::go_out:
		//注射が終わったら右へ移動
		needle_pos.x += 5;
		patient_pos.x += 5;
		liquid_pos.x += 5;
		break;
	default:
		break;
	}
}

void NeedleAndPatient::Draw() const
{
	DrawBox(260, 10, 400, 250, 0xffffff, FALSE);
	//列の仮表示
	DrawRotaGraph(120, 400, 1.5, 0, column[0], TRUE);

	//液体の表示
	DrawBox((int)liquid_pos.x, (int)liquid_pos.y+(int)liquid_size-10, (int)liquid_pos.x+140, 250, 0x00ff00, TRUE);

	//注射器の画像表示
	DrawRotaGraph((int)needle_pos.x, (int)needle_pos.y, 1, 0, needle_image[0], TRUE);
	//患者の表示
	//DrawRotaGraph((int)needle_pos.x, 420, 2.8, 0, patient[0], TRUE);
	DrawRotaGraphF(patient_pos.x, patient_pos.y,p_size,0, patient[0], TRUE);
	//very tired 50以下
	//tired 90以下
	//good_nomal 100
	//fine? 110以上
	//very fine 150以上

	char state[20];
	if (patient_sum <= 50)
	{
		DrawFormatString(patient_pos.x,patient_pos.y, 0x000000, "verytired");
	}
	else if (patient_sum <= 90)
	{
		DrawFormatString(patient_pos.x, patient_pos.y, 0x000000, "tired");
	}else if (patient_sum >= 150)
	{
		DrawFormatString(patient_pos.x, patient_pos.y, 0x000000, "veryfine");
	}
	else if (patient_sum >= 110)
	{
		DrawFormatString(patient_pos.x, patient_pos.y, 0x000000, "fine?");
	}
	else {
		DrawFormatString(patient_pos.x, patient_pos.y, 0x000000, "good");
	}

	DrawFormatString(100, 40, 0x000000, "el_sum:%d", el_sum);
	DrawFormatString(100, 100, 0x000000, "patient_sum:%d", patient_sum);
	DrawFormatString(100, 60, 0x000000, "liquid_y:%d", (int)liquid_pos.y + (int)liquid_size);
	DrawFormatString(100, 80, 0x000000, "stop_y:%d", stop_y);

	//止めるとこの仮表示↓
	if (needle_pos.y >= 145)
	{
		DrawBox(260, stop_y, 400, stop_y - 5, 0xff0000, TRUE);
		DrawBox(260, stop_y, 400, stop_y + 5, 0xff0000, TRUE);
	}
}
