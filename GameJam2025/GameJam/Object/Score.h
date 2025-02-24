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
	int score;				//初期スコア
	int patient;			//患者の人数

	int addscore;			//加算するスコア
	int new_score;			//新しいスコア
	int old_score;			//前回スコア
	int eventline;			//イベント線(仮)

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	void Evaluate();
};

