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
	int eventline;			//イベント線(仮)

public:
	Score();
	~Score();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	void Evaluate();
};

