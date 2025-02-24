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

	ReadTxt();
	
}

void Score::Update() 
{
	WriteTxt();
	Evaluate();
}

void Score::Draw() const
{
	for (int i = 0; i < 3; i++)
	{
		DrawFormatString(300, 10 + (i * 20), GetColor(255, 255, 255), "%dNp : %d", patient_array[i], score_array[i], TRUE);
	}
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

void Score::ReadTxt()
{
	ifstream ifs_txt_file(txt_file_path);				//読み込むファイルを開く
	int i = 0;

	//一行ずつ読み込む
	while (getline(ifs_txt_file, str_buf))
	{
		istringstream i_stream(str_buf);				//「,」区切りごとにデータを読み込む

		//スコアと患者の人数に分けて読み込む
		if (getline(i_stream, patient_str, ',') && getline(i_stream, score_str, ','))
		{
			int score = stoi(score_str);				//string型からint型に変換
			score_array[i] = score;

			int patient = stoi(patient_str);			//string型からint型に変換
			patient_array[i] = patient;

		}

		i++;
	}
}

void Score::WriteTxt()
{
	ofstream ofs_txt_file(txt_file_path);				//書き込むファイルを開く

	for (int i = 0; i < 3; i++)
	{
		ofs_txt_file << patient_array[i];				//配列に書き込む
		ofs_txt_file.put(',');
		ofs_txt_file << score_array[i];					//配列に書き込む
		ofs_txt_file.put('\n');

	}
}
