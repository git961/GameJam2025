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
	addscore = 100;
	red_line_location = 100;
	event_line_location = 200;
}

void Score::Update() 
{
	Evaluate();

	diff = std::abs(red_line_location - event_line_location);


}

void Score::Draw() const
{
}

void Score::Finalize()
{

}


//タイミング評価処理
void Score::Evaluate()
{
	eEvaluation evaluation = eEvaluation::eGood;		//変数にenum classのメンバーを設定

	if (diff >= 900)
	{
		evaluation = eEvaluation::ePerfect;
	}
	else if (diff >= 500)
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
		DrawFormatString(200, 10, GetColor(255, 255, 255), "Perfect", TRUE);
		addscore = 150;

		break;
	case eEvaluation::eGood:
		DrawFormatString(200, 10, GetColor(255, 255, 255), "Good", TRUE);
		addscore = 100;

		break;
	case eEvaluation::eBad:
		DrawFormatString(200, 10, GetColor(255, 255, 255), "Bad", TRUE);
		addscore = 0;

		break;
	default:
		break;
	}
}
