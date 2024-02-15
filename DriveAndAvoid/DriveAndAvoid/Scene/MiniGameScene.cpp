#include "MiniGameScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <chrono>
#include <thread>
#include <cstdlib> // �ǉ�

MiniGameScene::MiniGameScene()
{
    SetFontSize(50);
    // �����̃V�[�h�l��ݒ肷��
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

MiniGameScene::~MiniGameScene()
{

}

void MiniGameScene::Initialize()
{
    int image = LoadDivGraph("Resource/images/color.png", 4, 4, 1, 50, 50, color);

    // �ǂݍ��݃G���[�`�F�b�N
    if (image == -1)
    {
        throw("�摜�̓ǂݍ��݂Ɏ��s���܂���");
    }

    // �摜�̕\���ʒu��������
    for (int i = 0; i < 10; ++i)
    {
        // ��ʓ��Ɏ��܂�悤�ɉ摜�̈ʒu�𒲐�
        while (true)
        {
            // �摜�̈ʒu�������_���Ɍ���
            imagePositions[i].x = rand() % (600 - 50); // x���W�������_���ɐ����i�摜�̕����l���j
            imagePositions[i].y = rand() % (400 - 50); // y���W�������_���ɐ����i�摜�̍������l���j

            // �d�Ȃ���`�F�b�N
            bool overlap = false;
            for (int j = 0; j < i; ++j)
            {
                if (abs(imagePositions[i].x - imagePositions[j].x) < 50 && abs(imagePositions[i].y - imagePositions[j].y) < 50)
                {
                    overlap = true;
                    break;
                }
            }

            // �d�Ȃ肪�Ȃ���΃��[�v�𔲂���
            if (!overlap)
            {
                break;
            }
        }
    }

    // �r���h�V�[�����؂�ւ�邽�тɃ����_���ȉ摜�̃C���f�b�N�X������
    currentImageIndex = std::vector<int>(10); // �v�f��10��vector��������
    for (int i = 0; i < 10; ++i)
    {
        currentImageIndex[i] = rand() % 4; // 0����3�܂ł̃����_���Ȑ��𐶐�
    }
}



// �X�V����
eSceneType MiniGameScene::Update()
{
    // �摜�̈ʒu�������_���Ɉړ�������
    for (int i = 0; i < 10; ++i)
    {
        // �摜�̈ʒu�����������_���ɕύX
        imagePositions[i].x += (rand() % 11) - 5; // -5����5�܂ł̃����_���Ȑ���������
        imagePositions[i].y += (rand() % 11) - 5; // -5����5�܂ł̃����_���Ȑ���������

        // �摜����ʊO�ɏo�Ȃ��悤�ɂ���
        if (imagePositions[i].x < 0) imagePositions[i].x = 0;
        if (imagePositions[i].x > (600 - 50)) imagePositions[i].x = 600 - 50;
        if (imagePositions[i].y < 0) imagePositions[i].y = 0;
        if (imagePositions[i].y > (400 - 50)) imagePositions[i].y = 400 - 50;
    }

    return GetNowScene();
}

// �`�揈��
void MiniGameScene::Draw() const
{

    // ��ʂ��N���A
    ClearDrawScreen();

    // �Œ肳�ꂽ�ʒu�Ƀ����_���ȉ摜��\��
    for (int i = 0; i < 10; ++i)
    {
        DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // �摜��\��
    }
    // ��ʂ��X�V
    ScreenFlip();
}

// �I������
void MiniGameScene::Finalize()
{

}

// ���݂̃V�[�������擾
eSceneType MiniGameScene::GetNowScene() const
{
    return eSceneType::E_MINIGAME;
}