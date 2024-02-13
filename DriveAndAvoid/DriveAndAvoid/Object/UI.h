#pragma once


class UI
{
private:
	int Num[10];
	int image;
	int cnt;
	bool timeFlg;
public:
	UI();
	~UI();
	void Initialize();   //‰Šú‰»ˆ—
	void Update();       //XVˆ—
	void Draw();         //•`‰æˆ—
	void Finalize();     //I—¹ˆ—



public:

	int GetTimeFlg();

private:

};

