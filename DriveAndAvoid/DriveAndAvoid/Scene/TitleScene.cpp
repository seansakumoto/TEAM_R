#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() :background_image(NULL),credit_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}


//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.bmp");
	credit_image = LoadGraph("Resource/images/Credit.png");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (credit_image == -1)
	{
		throw("Resource/image/Credit.png������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cursor.bmp������܂���\n");
	}
}


//�X�V����
eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//�P�ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 4)
		{
			menu_cursor = 0;
		}
	}


	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//�P�ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 4;
		}
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
			case 0:
				return eSceneType::E_CREDIT;
				
			case 1:
				return eSceneType::E_RANKING_DISP;

			case 2:
				return eSceneType::E_HELP;

			case 3:
				return eSceneType::E_END;

			case 4:
				return eSceneType::E_MAIN;
		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}


//�`�揈��
void TitleScene::Draw()const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�N���W�b�g�摜�̕`��
	DrawGraph(120, 360, credit_image, TRUE);

	//���j���[�摜�̕`��
	DrawGraph(120, 200, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}


//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}


//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene()const
{
	return eSceneType::E_TITLE;
}