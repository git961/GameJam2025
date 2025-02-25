#include "Score.h"
#include "DxLib.h"

Score::Score()
{

}

Score::~Score()
{

}

void Score::Initialize() 
{
	addscore = 0;
	red_line_location = 100;
	event_line_location = 200;
	total_score = 0;
	time_count = 0;

	just_perfect = LoadGraph("Resource\\Image\\InGame\\timeing\\Perfect.PNG");
	just_good = LoadGraph("Resource\\Image\\InGame\\timeing\\Good.PNG");
	just_bad = LoadGraph("Resource\\Image\\InGame\\timeing\\Bad.PNG");
	p_se= LoadSoundMem("Resource/Sounds/SE/Perfect.mp3");
	g_se= LoadSoundMem("Resource/Sounds/SE/good.mp3");
	b_se= LoadSoundMem("Resource/Sounds/SE/Butt.mp3");

	check_just = false;

}

void Score::Update()
{
	//diff = std::abs(red_y - event_y);
	if (check_just == true)
	{
		time_count++;

		if (time_count > 30)
		{
			time_count = 0;
			check_just = false;
		}
	}
}

void Score::Draw() const
{
	if (check_just == true)
	{
		if (diff <= 10)
		{
			DrawGraph(200, 0, just_perfect, TRUE);
		}
		else if (diff <= 30)
		{
			DrawGraph(200, 0, just_good, TRUE);
		}
		else
		{
			DrawGraph(200, 0, just_bad, TRUE);
		}
	}
}

void Score::Finalize()
{

}

void Score::AddScore(int red_y, int event_y)
{
	diff = std::abs(red_y - event_y);
	check_just = true;
	Evaluate();
}


//タイミング評価処理
void Score::Evaluate()
{
	eEvaluation evaluation = eEvaluation::eGood;		//変数にenum classのメンバーを設定

	if (diff <= 10)
	{
		evaluation = eEvaluation::ePerfect;
		PlaySoundMem(p_se, DX_PLAYTYPE_BACK, TRUE);
	}
	else if (diff <= 30)
	{
		evaluation = eEvaluation::eGood;
		PlaySoundMem(g_se, DX_PLAYTYPE_BACK, TRUE);
	}
	else
	{
		evaluation = eEvaluation::eBad;
		PlaySoundMem(b_se, DX_PLAYTYPE_BACK, TRUE);
	}

	switch (evaluation)
	{
	case eEvaluation::ePerfect:
		addscore = 150;

		break;
	case eEvaluation::eGood:
		addscore = 100;

		break;
	case eEvaluation::eBad:
		addscore = 0;

		break;
	default:
		break;
	}

	//スコアを加算
	total_score += addscore;
}
