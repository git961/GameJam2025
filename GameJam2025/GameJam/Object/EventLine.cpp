#include "EventLine.h"
#include "../Utility/PadInputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

EventLine::EventLine()
{
	//画像を読み込む
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Image/InGame/triangle.png");
	triangle_img.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Image/InGame/event_line_range.png");
	range_img.push_back(tmp[0]);

	Initialize();
}

EventLine::~EventLine()
{
}

void EventLine::Initialize()
{
	//240.0fは現在の画面の半分のサイズ+10.0f
	stop_line_bottom = 250.0f;
	stop_line_up = 10.0f;
	//120.0fは画面の半分のサイズのさらに半分
	location.y = 180.0f;
	location.x = 450.0f;
	stop_location_y = 0;
	is_moving_up = true;
	is_stop = false;
	is_start = false;
	speed = 6.0f;
}

void EventLine::Update()
{
	if (is_start == false) { return; }

	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (is_stop == false)
	{
		//もし上の限界値までｙが来たら
		if (stop_line_up > location.y)
		{
			//上に上がるのを止める
			is_moving_up = false;
		}

		//もし下の限界値までｙが来たら
		if (stop_line_bottom < location.y)
		{
			is_moving_up = true;
		}

		//もし上がって良かったら
		if (is_moving_up == true)
		{
			location.y -= speed;
		}
		else
		{
			location.y += speed;
		}
	}

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress
		|| CheckHitKey(KEY_INPUT_J)==TRUE)
	{
		is_stop = true;
		stop_location_y = (int)location.y;
	}

}

void EventLine::Draw() const
{
	//仮背景　見やすいように
	//DrawBox(0, 0, 640, 480, 0x999999, TRUE);

	DrawRotaGraph(450,130, 1, 0, range_img[0], TRUE);

	if (is_start == true)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, triangle_img[0], TRUE);
	}

	//DrawFormatString(100, 160, 0x000000, "line_y:%f",location.y);
	//DrawFormatString(100, 180, 0x000000, "stop_locationy:%d",stop_location_y);
	//DrawTriangleAA(location.x, location.y, location.x + 30.0f, location.y + 30.0f, location.y - 30.0f,location.x - 30.0f, location.y - 30.0f, 0xffffff, TRUE);
	//DrawTriangleAA(location.x, location.y, location.x + 30.0f, location.y - 30.0f, location.x + 30.0f, location.y + 30.0f, 0xffffff, TRUE);
}

int EventLine::GetLineStopY()
{
	return stop_location_y;
}

bool EventLine::CheckStop()
{
	//動きが止まっていたらtrueを返す
	if (is_stop == true)
	{
		return true;
	}
	return false;
}

void EventLine::Stop()
{
	is_start = false;
	Initialize();
}
