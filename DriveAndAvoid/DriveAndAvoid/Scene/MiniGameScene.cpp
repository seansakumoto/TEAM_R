#include "MiniGameScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

MiniGameScene::MiniGameScene() :background_image(NULL)
{

}



MiniGameScene::~MiniGameScene()
{

}

//����������
void MiniGameScene::Initialize()
{
    // �摜�̓ǂݍ���
    background_image = LoadGraph("Resource/images/backimage.png");
    background_image1 = LoadGraph("Resource/images/backimagehelp.png");

    // �G���[�`�F�b�N
    if (background_image == -1)
    {
        throw("Resource/images/backimagehelp.png������܂���\n");
    }

    if (background_image1 == -1)
    {
        throw("Resource/images/backimage.png������܂���\n");
    }
}


//�X�V����
eSceneType MiniGameScene::Update()
{
    // B�{�^���������ꂽ��A�摜��؂�ւ���
    if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
    {
        // �摜��؂�ւ���
        if (currentImage == 0) {
            currentImage = 1;
        }
        else {
            currentImage = 0;
        }
    }

    // A�{�^���������ꂽ��A�^�C�g���ɖ߂�
    if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
    {
        return eSceneType::E_MAIN;
    }

    return GetNowScene();
}


//�`�揈��
void MiniGameScene::Draw()const
{
    // �ǂݍ��񂾉摜�̕\��
    if (currentImage == 0) {
        DrawGraph(0, 0, background_image, TRUE);
    }
    else {
        DrawGraph(0, 0, background_image1, TRUE);
    }
}

//�I������
void MiniGameScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	
}

//���݂̃V�[�������擾
eSceneType MiniGameScene::GetNowScene()const
{
	return eSceneType::E_MINIGAME;
}