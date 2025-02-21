#pragma once
class NeedleAndPatient
{
private:
	class EventLine* event_line;

	int stop_y;//ストップさせる高さ
public:
	NeedleAndPatient(class EventLine* set_class);
	~NeedleAndPatient();
	void Initialize();//初期化
	void Update();
	void Draw()const;

	//ストップさせる高さのｙ座標を返す
	int GetStopY() { return stop_y; }
};

