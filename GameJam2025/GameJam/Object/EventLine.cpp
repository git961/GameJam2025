#include "EventLine.h"
#include "../Utility/PadInputManager.h"
#include "DxLib.h"

EventLine::EventLine()
{
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
	location.y = 120.0f;
	location.x = 400.0f;
	stop_location_y = 0;
	is_moving_up = true;
	is_stop = false;
}

void EventLine::Update()
{
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
			location.y -= 2.4f;
		}
		else
		{
			location.y += 2.4f;
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
	DrawBox(0, 0, 640, 480, 0x999999, TRUE);
	if (is_moving_up == true)
	{
		DrawTriangleAA(location.x, location.y, location.x + 20.0f, location.y - 20.0f, location.x + 20.0f, location.y + 20.0f, 0x00ffff, TRUE);
	}
	else
	{
		DrawTriangleAA(location.x, location.y, location.x + 20.0f, location.y - 20.0f, location.x + 20.0f, location.y + 20.0f, 0xffff00, TRUE);

	}
	//DrawTriangleAA(location.x, location.y, location.x + 30.0f, location.y + 30.0f, location.y - 30.0f,location.x - 30.0f, location.y - 30.0f, 0xffffff, TRUE);
	//DrawTriangleAA(location.x, location.y, location.x + 30.0f, location.y - 30.0f, location.x + 30.0f, location.y + 30.0f, 0xffffff, TRUE);
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
