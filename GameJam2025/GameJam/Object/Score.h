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

	int addscore;			//加算するスコア
	int total_score;			//スコア
	int red_line_location;
	int event_line_location;

	int diff;

public:
	Score();
	~Score();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();
	//距離の判定をしてスコアの加算をする
	void AddScore(float red_y, float event_y);
	//Totalスコアを返す
	int GetTotalScore() { return total_score; }

	void Evaluate();
};

