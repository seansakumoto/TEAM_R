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
	DrawFormatString(0, 0, GetColor(0, 255, 0), "�N���W�b�g�\�L\n");
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


