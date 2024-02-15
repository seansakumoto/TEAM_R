#include "CreditScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

CreditScene::CreditScene():back_image(NULL)
{

}

CreditScene::~CreditScene()
{

}


//����������
void CreditScene::Initialize()
{
	back_image = LoadGraph("Resource/images/Credit_back_image.png");

	if (back_image == -1)
	{
		throw("Credit_back_image.png������܂���");
	}
}


//�X�V����
eSceneType CreditScene::Update()
{
	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}


//�`�揈��
void CreditScene::Draw()const
{
	DrawGraph(0, 0, back_image, TRUE);

	//�����񋟎җl�Љ�
	DrawFormatString(25, 100, GetColor(255,0,255), "�����f�ޒ񋟌�");
	DrawFormatString(25, 140, GetColor(255,255,255), "Pocketsound(https://pocket-se.info/)");
	DrawFormatString(25, 160, GetColor(255,255,255), "������(https://maou.audio/)");
	DrawFormatString(25, 180, GetColor(255, 255, 255), "���ʉ����{(https://soundeffect-lab.info/)");
	DrawFormatString(25, 200, GetColor(255, 255, 255), "DOVA-SYNDROME(https://dova-s.jp/)");
	
	//�摜�񋟎җl�Љ�
	DrawFormatString(25, 300, GetColor(255, 0, 255),"�摜�f�ޒ񋟌�");
	DrawFormatString(25, 320, GetColor(255, 255, 255), "�ς�ۂ���(https://pawaposuke.com/)");
	DrawFormatString(25, 340, GetColor(255, 255, 255), "���炷�Ƃ�(https://www.irasutoya.com/)");
}


//�I��������
void CreditScene::Finalize()
{
	DeleteGraph(back_image);
}


//���݂̃V�[�������擾
eSceneType CreditScene::GetNowScene()const
{
	return eSceneType::E_CREDIT;
}


