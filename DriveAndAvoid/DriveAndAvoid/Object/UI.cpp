#include "UI.h"
#include "DxLib.h"


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
	timeFlg = false;

	//�摜�̓ǂݍ���
	LoadDivGraph("Resource/images/Number_r.bmp", 10, 10, 1, 20, 30, Num); // �摜�̕����ǂݍ���
	////�G���[�`�F�b�N
	//if (.../)
	//{
	//	throw(".../");
	//}
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
	DrawGraph(0, 25, Num[(cnt % 10000) / 1000], TRUE);
	DrawGraph(20, 25, Num[(cnt % 1000) / 100], TRUE);

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











