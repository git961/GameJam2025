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
	string str_buf;			//バフ
	string str_conma_buf;	//カンマ
	string txt_file_path = "C:\\GameJam2025\\GameJam2025\\GameJam\\Resource\\Ranking\\Ranking.txt";

	ifstream ifs_txt_file(txt_file_path);				//読み込むファイルを開く
	ofstream ofs_txt_file(txt_file_path);				//書き込むファイルを開く

	while (getline(ifs_txt_file, str_buf))
	{
		istringstream i_stream(str_buf);				//「,」区切りごとにデータを読み込む

		while (getline(i_stream, str_conma_buf, ','))
		{
			ofs_txt_file << str_conma_buf << ',';		//ファイルに書き込む
		}
		ofs_txt_file << endl;							//改行
	}

	Evaluate();
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
