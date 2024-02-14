#include "Enemy.h"
#include "DxLib.h"
#include"../Utility/InputControl.h"
#include"../Scene/GameMainScene.h"
#include <string>

Enemy::Enemy() : location(0.0f), box_size(0.0f) 
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

    // �ʒu�ⓖ���蔻��̑傫����ݒ肷��
    location = Vector2D(x, y);
    box_size = Vector2D(width, height);
}

void Enemy::Update()
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

}

void Enemy::Finalize()
{
    // ���\�[�X�̉���Ȃǂ̏I���������s��
    DeleteGraph(image);
}

int Enemy::GetY() const {
    return y;
}


// �������󂯎��R���X�g���N�^�[�̎���
Enemy::Enemy(int initialX, int initialY) : x(initialX), y(initialY)
{
    // �����Ŏ󂯎�����l���g��������������
}

Vector2D Enemy::GetLocation() const {
    return location;
}

Vector2D Enemy::GetBoxSize() const {
    return box_size;
}