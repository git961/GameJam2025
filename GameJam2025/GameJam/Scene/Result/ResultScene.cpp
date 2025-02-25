#include "ResultScene.h"
#include "../../Utility/PadInputManager.h"
#include"../../Object/Score.h"
#include "DxLib.h"

ResultScene::ResultScene()
{
	score = new Score;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	ranking_image = LoadGraph("Resource\\Ranking\\result.png");
	BGM = LoadSoundMem("Resource/Sounds/BGM/ResultorendBGM.mp3");
	SE = LoadSoundMem("Resource/Sounds/SE/MV.mp3");
	score->Initialize();
	ReadTxt();
}

eSceneType ResultScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (CheckSoundMem(BGM) == 0)
	{
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, FALSE);
	}

	//Bを押したらタイトルへ戻る
	if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePress)
	{
		PlaySoundMem(SE, DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::eTitle;
	}

	score->Update();
	ComparisonScore();
	WriteTxt();

	return GetNowSceneType();
}

void ResultScene::Draw() const
{	
	DrawString(10, 10, "Result\n", GetColor(255, 255, 255));
	DrawString(10, 26, "B:Title", GetColor(255, 255, 255));
	DrawExtendGraph(0, 0, 640, 480, ranking_image, TRUE);
	

	for (int i = 0; i < 3; i++)
	{
		SetFontSize(24);

		DrawFormatString(300, 203 + (i * 70), GetColor(0, 0, 0), "%d   %d", patient_array[i], score_array[i], TRUE);
	}

	SetFontSize(16);

	score->Draw();
}

void ResultScene::Finalize()
{
	StopSoundMem(BGM);
}

eSceneType ResultScene::GetNowSceneType() const
{
	//自分のsecenetypeを返す
	return eSceneType::eResult;
}

//テキスト読み込み処理
void ResultScene::ReadTxt()
{
	ifstream ifs_txt_file(txt_file_path);				//読み込むファイルを開く
	int i = 0;

	//一行ずつ読み込む
	while (getline(ifs_txt_file, str_buf))
	{
		istringstream i_stream(str_buf);				//列をistringstreamに変換

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

//テキスト書き込み処理
void ResultScene::WriteTxt()
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

//スコア比較処理
void ResultScene::ComparisonScore()
{
	int old_score;										//Scoreの前回情報
	int old_patient;									//Patientの前回情報

	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (score_array[i] <= score_array[j])
			{
				old_score = score_array[i];				//前回情報を変数に入れる
				old_patient = patient_array[i];

				score_array[i] = score_array[j];		//新しい情報をscore_array[i]に入れる
				patient_array[i] = patient_array[j];

				score_array[j] = old_score;				//前回情報をscore_array[j]に入れる
				patient_array[j] = old_patient;

			}
		}
	}
}
