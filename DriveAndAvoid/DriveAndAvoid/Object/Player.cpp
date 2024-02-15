#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"


Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),invincible(0),reviv(0),
angle(0.0f),
						speed(0.0f), barrier_count(0),life(0),
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
	location = Vector2D(250.0f, 480.0f / 5.0f * 4);
	box_size = Vector2D(31.0f, 30.0f);
	angle = 0.0f;
	speed = 7.0f;//�v���C���[�̑��x�f�t�H���g5
	barrier_count = 3;
	life = 3;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/player.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/player.png������܂���\n");
	}


	//SE�̓ǂݍ���
	sound_effect[0] = LoadSoundMem("Resource/sounds/SE_player_move.ogg");
	sound_effect[1] = LoadSoundMem("Resource/sounds/SE_player_avoid.ogg");
	sound_effect[2] = LoadSoundMem("Resource/sounds/SE_player_hit.ogg");
	sound_effect[3] = LoadSoundMem("Resource/sounds/SE_player_break.ogg");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (sound_effect[i]==-1)
		{
			throw("Resource/sounds/SE_player[%d]��������܂���", i);
		}
	}
	//if (sound_effect[0] == -1)
	//{
	//	throw("Resource/sounds/SE_player_move.ogg�������患");
	//}

	////�G���[�`�F�b�N
	//if (sound_effect[1] == -1)
	//{
	//	throw("Resource/sounds/SE_player_avoid.ogg�������患");
	//}

	////�G���[�`�F�b�N
	//if (sound_effect[2] == -1)
	//{
	//	throw("Resource/sounds/SE_player_hit.ogg�������悧");
	//}

	////�G���[�`�F�b�N
	//if (sound_effect[3] == -1)
	//{
	//	throw("Resource/sounds/SE_player_break.ogg�������悡");
	//}

	//���ʂ̒���
	for (int i = 0; i < 4; i++)
	{
		ChangeVolumeSoundMem(200, sound_effect[i]);
	}
	/*ChangeVolumeSoundMem(200, sound_effect[0]);
	ChangeVolumeSoundMem(200, sound_effect[1]);
	ChangeVolumeSoundMem(200, sound_effect[2]);
	ChangeVolumeSoundMem(200, sound_effect[3]);*/
}


//�X�V����
void Player::Update()
{
	//����s���
	if (!is_active)
	{
		/*angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;*/

		////�G�ɂԂ������Ƃ��̏���
		//if (barrier == nullptr)
		//{
		//	barrier = new Barrier;
		//	invincible = 0;
		//	reviv = 30;
		//	PlaySoundMem(sound_effect[2], DX_PLAYTYPE_BACK, TRUE);
		//	PlaySoundMem(sound_effect[3], DX_PLAYTYPE_BACK, TRUE);
		//}
	}


	//�ړ�����
	Movement();


	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{

	}

	if (CheckSoundMem(sound_effect[0]) == 0)
	{
		PlaySoundMem(sound_effect[0], DX_PLAYTYPE_BACK, TRUE);
	}

	//�o���A����
	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier = new Barrier;
		}
	}*/

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		invincible++;
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
			is_active = true;
		}
	}
}


//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	if (barrier != nullptr)
	{
		if (invincible<reviv/2)
		{
			DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
		}
		else
		{
			
		}
		if (invincible > reviv)
		{
			invincible = 0;
			reviv -= 4;
		}
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	}
	/*DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, FALSE);*/
	

	DrawFormatString(550, 350, GetColor(0, 255, 0), "%d", life);
	DrawFormatString(550, 370, GetColor(255, 255, 255), "%f", location.x);

	////�o���A����������Ă�����A�`����s��
	//if (barrier != nullptr)
	//{
	//	barrier->Draw(this->location);
	//}

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


void Player::DecLife()
{
	life--;
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


//�c�@�擾����
int Player::GetLife()const
{
	return life;
}


//�o���A���L�����H���擾
bool Player::IsBarrier()const
{
	return (barrier != nullptr);
}


//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	float MoveSizeX = 50;
	float MoveSizeY = 40;
	angle = 0.0f;
	//
	//
	//Vector2D move = Vector2D(0.0f);
	//angle = 0.0f;

	////�\���ړ�����
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	//{
	//	move += Vector2D(-100.0f, 0.0f);
	//	angle = -DX_PI_F / 18;
	//}
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	//{
	//	move += Vector2D(100.0f, 0.0f);
	//	angle = DX_PI_F / 18;
	//}
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	//{
	//	move += Vector2D(0.0f, -150.0f);
	//}
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	//{
	//	move += Vector2D(0.0f, 150.0f);
	//}

	//location += move;


	////��ʊO�ɍs���Ȃ��悤�ɐ�������
	//if ((location.x < 150.0f) || (location.x >= 640.0f - 180.0f) ||
	//	(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	//{
	//	location -= move;
	//}

 //   //�X�e�B�b�N�̓��͂��擾����
	//Vector2D stickInput = InputControl::GetLeftStick();

	//// �X�e�B�b�N��X�������̓��͂ɉ����ăv���C���[�L�����N�^�[���ړ�������
	//float moveSpeed = 6.0f; // �ړ����x��ݒ肷��

	//float moveXAmount = stickInput.x * moveSpeed; // �X�e�B�b�N�̓��͂ɉ����Ĉړ�����ʂ��v�Z X
	//float moveYAmount = stickInput.y * moveSpeed; // Y

	//Vector2D move = Vector2D(moveXAmount, moveYAmount); // �X�e�B�b�N�̈ړ���

	//�\���ړ�����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-MoveSizeX, 0.0f);
		angle = -DX_PI_F / 18;
		PlaySoundMem(sound_effect[1], DX_PLAYTYPE_BACK,TRUE);
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(MoveSizeX, 0.0f);
		angle = DX_PI_F / 18;
		PlaySoundMem(sound_effect[1], DX_PLAYTYPE_BACK, TRUE);
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -MoveSizeY);
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, MoveSizeY);
	}

	// �v���C���[�L�����N�^�[�̈ʒu���X�V����
	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x <= 0.0f+box_size.x) || (location.x >= 500.0f) ||
		(location.y <=0.0f) || (location.y >= 480.0f))
	{
		location -= move;
	}

}


