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
}

NeedleAndPatient::~NeedleAndPatient()
{
}

void NeedleAndPatient::Initialize()
{
	stop_y = 120;
	needle_pos.x = 320.0f;
	needle_pos.y = -270.0f;
}

void NeedleAndPatient::Update()
{
	if (needle_pos.y < 145)
	{
		needle_pos.y += 5.0f;
	}

	if (event_line->CheckStop() == true)
	{
		//注射する

		//注射が終わったら右へ移動
		needle_pos.x += 5;
	}
}

void NeedleAndPatient::Draw() const
{
	DrawBox(260, 10, 400, 250, 0xffffff, FALSE);
	//注射器の画像表示
	DrawRotaGraph((int)needle_pos.x, (int)needle_pos.y, 1, 0, needle_image[0], TRUE);
	//患者の表示
	DrawRotaGraph((int)needle_pos.x, 380, 2, 0, patient[0], TRUE);

	if (needle_pos.y > 145)
	{
		//止めるとこの仮表示↓
		DrawBox(260, stop_y, 400, stop_y - 10, 0xff0000, TRUE);
		DrawBox(260, stop_y, 400, stop_y + 10, 0xff0000, TRUE);
	}
}
