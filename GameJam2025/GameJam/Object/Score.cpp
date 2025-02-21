#include "Score.h"
#include "DxLib.h"

void Score::Initialize() 
{
	score = 0;
	patient = 0;

	addscore = 100;
	eventline = 1000;
}

void Score::Update() 
{
	Evaluate();
	WriteTxtFile();
	ReadTxtFile();
}

void Score::Draw()
{

}

void Score::Finalize()
{

}


//タイミング評価処理
void Score::Evaluate()
{
	eEvaluation evaluation = eEvaluation::eGood;	//変数にenum classのメンバーを設定

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

void Score::WriteTxtFile()
{
	ofstream outFile("C:\\GameJam2025\\GameJam2025\\GameJam\\Resource\\Ranking\\Ranking.txt");

	if (outFile.is_open())
	{
		
		outFile << score << " "<< patient << endl;
	}
	else
	{
		cerr << "ファイルを開けませんでした。" << endl;
	}
}

int Score::ReadTxtFile()
{
	ifstream file("C:\\GameJam2025\\GameJam2025\\GameJam\\Resource\\Ranking\\Ranking.txt");

	if (!file) {
		std::cerr << "ファイルを開けませんでした！" << std::endl;

		return 1;
	}

	// ファイルを1行ずつ読み込む
	string line;

	//ファイルを一行ずつ読み込み、配列に格納
	while (getline(file, line)) 
	{
		// 読み込んだ行を表示
		DrawFormatString(260, 10, GetColor(255, 255, 255), "%s\n", line.c_str(), TRUE);
	}

	// ファイルを閉じる
	file.close();

	return 0;
}