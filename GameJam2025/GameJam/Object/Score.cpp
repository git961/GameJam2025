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
	eventline = 1000;
}

void Score::Update() 
{
	Evaluate();
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

	if (eventline >= 900)
	{
		evaluation = eEvaluation::ePerfect;
	}
	else if (eventline >= 500)
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
