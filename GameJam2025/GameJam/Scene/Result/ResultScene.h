#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>

#include "../SceneBase.h"

using namespace std;//std::を省略

class ResultScene :
    public SceneBase
{
private:
    class Score* score;

    string str_buf;			//バフ
    string score_str;		//スコア
    string patient_str;			//患者の人数

    string txt_file_path = "Resource\\Ranking\\Ranking.txt";

    int score_array[4];     //スコア配列
    int patient_array[4];   //患者の人数配列
    int new_score;			//新しいスコア
    int new_patient;		//新しい患者の人数	
    int now_player_score;   //現在のプレイヤーのスコア
    int now_player_patient; //現在のプレイヤーの患者数

    int ranking_image;      //ランキングイメージ
    int SE;
    int BGM;

public:
    ResultScene();
    ~ResultScene();

    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;

    void ReadTxt();
    void WriteTxt();

    void ComparisonScore();

public:
    virtual eSceneType GetNowSceneType() const override;

};

