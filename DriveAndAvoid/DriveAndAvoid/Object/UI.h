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
	void Initialize();   //����������
	void Update();       //�X�V����
	void Draw();         //�`�揈��
	void Finalize();     //�I��������



public:

	int GetTimeFlg();

private:

};

