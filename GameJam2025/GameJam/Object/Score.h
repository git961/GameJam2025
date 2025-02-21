#pragma once

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
	int addscore;			//加算するスコア
	int eventline;			//イベント線(仮)

public:
	Score();
	~Score();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();		
	void Evaluate();
};

