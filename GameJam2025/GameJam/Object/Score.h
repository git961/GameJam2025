#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;//std::を省略


//enum評価クラス
enum class eEvaluation
{
	ePerfect,	//パーフェクト
	eGood,		//グッド
	eBad		//バッド

};

class Score
{
private:
	int score_array[3];
	int patient_array[3];

	string str_buf;			//バフ
	string score_str;		//スコア
	string patient_str;			//患者の人数

	string txt_file_path = "C:\\GameJam2025\\GameJam2025\\GameJam\\Resource\\Ranking\\Ranking.txt";

	int addscore;			//加算するスコア
	int new_score;			//新しいスコア
	int new_patient;		//新しい患者の人数	
	int eventline;			//イベント線(仮)

public:
	Score();
	~Score();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	void Evaluate();

	void ReadTxt();
	void WriteTxt();

	void ComparisonScore();
};

