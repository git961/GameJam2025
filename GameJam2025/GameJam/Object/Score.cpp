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
}

void Score::Update()
{
	//diff = std::abs(red_y - event_y);
	Evaluate();
}

void Score::Draw() const
{
	if (diff <= 10)
	{
		DrawFormatString(200, 10, GetColor(0, 0, 0), "Perfect", TRUE);
	}
	else if (diff <= 20)
	{
		DrawFormatString(200, 10, GetColor(0, 0, 0), "Good", TRUE);
	}
	else
	{
		DrawFormatString(200, 10, GetColor(0, 0, 0), "Bad", TRUE);
	}
}

void Score::Finalize()
{

}

void Score::AddScore(float red_y, float event_y)
{
	diff = std::abs(red_y - event_y);
	Evaluate();
}


//タイミング評価処理
void Score::Evaluate()
{
	eEvaluation evaluation = eEvaluation::eGood;		//変数にenum classのメンバーを設定

	if (diff <= 10)
	{
		evaluation = eEvaluation::ePerfect;
	}
	else if (diff <= 20)
	{
		evaluation = eEvaluation::eGood;
	}
	else
	{
		evaluation = eEvaluation::eBad;
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
