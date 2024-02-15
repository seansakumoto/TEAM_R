#include "UI.h"
#include "DxLib.h"
#include "../Scene/GameMainScene.h"


UI::UI() 
{
	
}


UI::~UI()
{

}


//����������
void UI::Initialize()
{
	cnt = 0;
	startcnt = 180;
	timeFlg = false;

	//�摜�̓ǂݍ���
	LoadDivGraph("Resource/images/number_r1.png", 10, 10, 1, 30, 60, Num); // �摜�̕����ǂݍ���

}



//�X�V����
void UI::Update()
{
	
		++cnt;
		if (cnt >= 6000)
		{
			timeFlg = true;
		}

	

}


//�`�揈��
void UI::Draw()
{
	SetFontSize(50);
	DrawFormatString(510, 10, GetColor(0, 255, 0), "TIME");
	DrawGraph(530, 60, Num[(cnt % 10000) / 1000], TRUE);
	DrawGraph(560, 60, Num[(cnt % 1000) / 100], TRUE);
	/*DrawFormatString(520, 10, GetColor(0, 255, 0), "�X�R�A");
	DrawGraph(520, 30,  , TRUE);*/
	//DrawFormatString(550, 350, GetColor(0, 255, 0), "%d", life);

}


//�I��������
void UI::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

}

int UI::GetTimeFlg()
{
	return timeFlg;
}











