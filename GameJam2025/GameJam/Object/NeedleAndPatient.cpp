#include "NeedleAndPatient.h"
#include "DxLib.h"

NeedleAndPatient::NeedleAndPatient(EventLine* set_class)
{
	event_line = set_class;
	Initialize();
}

NeedleAndPatient::~NeedleAndPatient()
{
}

void NeedleAndPatient::Initialize()
{
	stop_y = 120;
}

void NeedleAndPatient::Update()
{

}

void NeedleAndPatient::Draw() const
{
	DrawBox(260, 10, 400, 250, 0xffffff, FALSE);
	//止めるとこの仮表示↓
	DrawBox(260, stop_y, 400, stop_y-10, 0xff0000, TRUE);
	DrawBox(260, stop_y, 400, stop_y+10, 0xff0000, TRUE);
}
