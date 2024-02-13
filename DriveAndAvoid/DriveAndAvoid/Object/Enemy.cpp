#include "Enemy.h"
#include "DxLib.h"
#include"../Utility/InputControl.h"
#include"../Scene/GameMainScene.h"

#include <string>


Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
    // ��Q���̉摜��ǂݍ���
    image = LoadGraph("Resource/images/bariked.png");

    // �����ʒu�������_���ɐݒ肷��
    int xPositions[] = { 15, 115, 215, 315, 415 };
    x = xPositions[GetRand(5)];

    y = 0; // ��ʂ̏�[�����Q����z�u����

    // �ړ����x��ݒ肷��
    speed = 5; // �ړ����x�i�C�ӂ̒l�j

    // ��Q���̃T�C�Y��ݒ肷��
    width = 75; // ��Q���̕�
    height = 75; // ��Q���̍���
}

void Enemy::Updata()
{
    // ��Q���̈ړ�����
    y += speed; // y���W���������Ɉړ�����

    // ��Q������ʊO�ɏo����Ĕz�u����
    if (y > 500) {
        // �����ʒu���Đݒ肷��
        int xPositions[] = { 15, 115, 215, 315, 415 };
        x = xPositions[GetRand(5)];
        y = 0; // ��ʂ̏�[����Ĕz�u����
    }
}

void Enemy::Draw() const
{
    // ��Q���̉摜��`�悷��
    DrawGraph(x, y, image, TRUE);

    // �摜�̌��݂̈ʒu��\������
    int drawX = x;
    int drawY = y - 20; // �摜�̏�ɕ\�����邽�߂� y ���W�𒲐�����
    std::string positionInfo = "X: " + std::to_string(x) + ", Y: " + std::to_string(y);
    DrawString(drawX, drawY, positionInfo.c_str(), GetColor(255, 255, 255));
}

void Enemy::Finalize()
{
    // ���\�[�X�̉���Ȃǂ̏I���������s��
    DeleteGraph(image);
}