#pragma once


class UI
{
private:
	int Num[10];
	int image;
	int cnt;
	bool timeFlg;
	int score;
	int startcnt;
public:
	UI();
	~UI();
	void Initialize();   //初期化処理
	void Update();       //更新処理
	void Draw();         //描画処理
	void Finalize();     //終了時処理



public:

	int GetTimeFlg();

private:

};

