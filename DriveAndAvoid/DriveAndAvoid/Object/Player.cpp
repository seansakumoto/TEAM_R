#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"



Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
						speed(0.0f), barrier_count(0),
barrier(nullptr)
{

}


Player::~Player()
{
	
}


//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(150.0f, 400.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 6.0f;//�v���C���[�̑��x�f�t�H���g5
	barrier_count = 3;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/car1pol.bmp");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���\n");
	}
}



//�X�V����
void Player::Update()
{
	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}


	//�ړ�����
	Movement();


	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}


//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	DrawFormatString(400, 350, GetColor(255, 255, 255), "%f", location.x);
	DrawFormatString(400, 370, GetColor(255, 255, 255), "%f", location.y);

	// �X�e�B�b�N�̈ړ��ʂ��擾����
	Vector2D stickInput = InputControl::GetLeftStick();

	// �X�e�B�b�N�̈ړ��ʂ�\������
	DrawFormatString(400, 390, GetColor(255, 255, 255), "Stick X: %f", stickInput.x);
	DrawFormatString(400, 410, GetColor(255, 255, 255), "Stick Y: %f", stickInput.y);


	//�o���A����������Ă�����A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}


//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}


//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}


//�ʒu���擾����
Vector2D Player::GetLocation()const
{
	return this->location;
}


//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}


//�����擾����
float Player::GetSpeed()const
{
	return this->speed;
}


//�o���A�����擾����
int Player::GetBarrierCount()const
{
	return this->barrier_count;
}


//�o���A���L�����H���擾
bool Player::IsBarrier()const
{
	return (barrier != nullptr);
}


//�ړ�����
void Player::Movement()
{
	
    //�X�e�B�b�N�̓��͂��擾����
	Vector2D stickInput = InputControl::GetLeftStick();

	// �X�e�B�b�N��X�������̓��͂ɉ����ăv���C���[�L�����N�^�[���ړ�������
	float moveSpeed = 6.0f; // �ړ����x��ݒ肷��

	float moveXAmount = stickInput.x * moveSpeed; // �X�e�B�b�N�̓��͂ɉ����Ĉړ�����ʂ��v�Z X
	float moveYAmount = stickInput.y * moveSpeed; // Y

	Vector2D move = Vector2D(moveXAmount, moveYAmount); // �X�e�B�b�N�̈ړ���

	// �\���L�[�̓��͂��擾����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT)) {
		move.x -= 100.0f; // �\���L�[�̍����͂ɉ����Ĉړ�����ʂ����炷
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT)) {
		move.x += 100.0f; // �\���L�[�̉E���͂ɉ����Ĉړ�����ʂ𑝂₷
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP)) {
		move.y -= 150.0f; // �\���L�[�̏���͂ɉ����Ĉړ�����ʂ����炷
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN)) {
		move.y += 150.0f; // �\���L�[�̉����͂ɉ����Ĉړ�����ʂ𑝂₷
	}

	// �v���C���[�L�����N�^�[�̈ʒu���X�V����
	location += move;

	// ��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < 150.0f) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y)) {
		location -= move;
	}

}


