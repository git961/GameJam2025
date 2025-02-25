#include "Column.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

Column::Column()
{
	//画像を読み込む
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	//240*112
	tmp = rm->GetImages("Resource/Image/InGame/back_column.png",14,14,1,240,112);
	for (int i = 0; i < 14; i++)
	{
		column_img.push_back(tmp[i]);
	}
	img_size = 1.5;
	location.x = 120.0f;
	location.y = 400.0f;
	img_num = 0;
	anim_cnt = 0;
	frame_cnt = 0;

	anim_state = AnimState::black;
}

Column::~Column()
{
}

void Column::Initialize()
{
}

void Column::AnimUpdate(bool is_black)
{

	switch (anim_state)
	{
	case AnimState::black:
		//0~3を表示
		if (anim_cnt++ > 2)
		{
			anim_cnt = 0;
			if (img_num++ >= 3)
			{
				img_num = 0;
			}
		}
		break;
	case AnimState::change_gray:
		//4~6黒から白へ
		if (anim_cnt++ > 2)
		{
			anim_cnt = 0;
			if (img_num++ >= 6)
			{
				img_num = 7;
			
				anim_state = AnimState::gray;
			}
		}

		break;
	case AnimState::gray:
		//7~10を表示
		if (anim_cnt++ > 2)
		{
			anim_cnt = 0;
			if (img_num++ >= 10)
			{
				img_num = 7;
			}
		}
		break;
	case AnimState::change_black:
		//11~13白から黒へ
		if (anim_cnt++ > 2)
		{
			anim_cnt = 0;
			if (img_num++ >= 13)
			{
				img_num = 0;
				anim_state = AnimState::black;
			}
		}
		break;
	}

	
	
}

void Column::Draw() const
{
	//後ろの列の表示
	DrawRotaGraph((int)location.x, (int)location.y, img_size, 0, column_img[img_num], TRUE);
}
