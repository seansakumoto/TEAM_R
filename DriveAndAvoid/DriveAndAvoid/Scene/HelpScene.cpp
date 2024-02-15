#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() :background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}


//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Control.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images.Cntrol.png������܂���\n");
	}
}


//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//�`�揈��
void HelpScene::Draw()const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(20, 100, "�w���v���", 0xffffff, 0);


	DrawString(20, 140, "������@", 0xffffff, 0);
	DrawString(20, 180, "�\������ňړ�", 0xffffff, 0);
	DrawString(20, 200, "START�{�^����pause", 0xffffff, 0);

	
	DrawString(20, 240, "�Q�[�����[��", 0xffffff, 0);
	DrawString(20, 280, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 300, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 320, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 340, "���񓖂���ƃQ�[���I�[�o�[�ł�", 0xffffff, 0);

	DrawString(150, 450, "B�{�^���������ă^�C�g���֖߂�", 0xffffff, 0);
}


//�I������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene()const
{
	return eSceneType::E_HELP;
}