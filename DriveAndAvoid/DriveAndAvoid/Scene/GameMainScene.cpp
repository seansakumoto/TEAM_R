#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <math.h>


GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL), pause_flag(TRUE), pause_image(NULL),
mileage(0), player(nullptr),
enemy(nullptr)
{

	for (int i = 0; i < 1; i++)
	{
		image = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	score = 0;
	//�����_�l��ǂݍ���
	ReadHighScore();

    //�摜�̓ǂݍ���
    back_ground = LoadGraph("Resource/images/back.bmp");
    barrier_image = LoadGraph("Resource/images/barrier.png");
    //int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120,enemy_image);
    // 
    // LoadGraph�œG�̉摜��ǂݍ���
    image = LoadGraph("Resource/images/barikedo1.png");
    //�|�[�Y�摜
    pause_image = LoadGraph("Resource/images/pause1.png");

	BGM = LoadSoundMem("Resource/sounds/Ride_out.mp3");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}

	if (image == -1)
	{
		throw("Resource/images/barikedo1.png������܂���\n");
	}

	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}

	if (image == -1)
	{
		throw("Resource/images/barikedo.png������܂���\n");
	}

	if (pause_image == -1)
	{
		throw("Resource/images/pause.png������܂���\n");
	}

	//�I�u�W�F�N�g�̐���
	player = new Player;
	enemy = new Enemy * [4];
	ui = new UI;


	//�I�u�W�F�N�g�̏�����
	player->Initialize();
	ui->Initialize();

    for (int i = 0; i < 4; i++)
    {
        enemy[i] = nullptr;
    }
    //
    pause_flag = FALSE;
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//// BGM���Đ�����Ă��炸�A�Đ��t���O�������Ă���ꍇ�͍Đ�����
	//if (!isBGMPlaying && CheckSoundMem(BGM) == false) {
	//	PlaySoundMem(BGM, DX_PLAYTYPE_BACK);
	//	isBGMPlaying = true; // BGM���Đ�����Ă����ԂɍX�V����
	//}

	// �|�[�Y�{�^���������ꂽ��|�[�Y�t���O��؂�ւ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;

	}

	// �|�[�Y�t���O�������Ă���ꍇ�͍X�V�������s��Ȃ�
	if (pause_flag)
	{
		StopSoundMem(BGM);
		return GetNowScene();
	}
	else
	{
		// �|�[�Y�t���O�������Ă��Ȃ��ꍇ�̏������L�q����

		if (CheckSoundMem(BGM) == false) {

			PlaySoundMem(BGM, DX_PLAYTYPE_BACK,false);
		}
		// �v���C���[�̍X�V
		player->Update();
		ui->Update();

		// �ړ������̍X�V
		mileage += (int)player->GetSpeed() + 5;

		// �G��������
		if (mileage / 20 % 100 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (enemy[i] == nullptr)
				{
					int type = GetRand(3) % 3;
					enemy[i] = new Enemy(type, image);
					enemy[i]->Initialize();
					break;
				}
			}
		}

		// �G�̍X�V�Ɠ����蔻��`�F�b�N
		for (int i = 0; i < 4; i++)
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->Updata(player->GetSpeed());

				// ��ʊO�ɍs������A�G���폜���ăX�R�A���Z
				if (enemy[i]->GetLocation().y >= 640.0f)
				{
					enemy_count[enemy[i]->GetType()]++;
					//�X�R�A���v�Z����
					score += 100;
					enemy[i]->Finalize();
					delete enemy[i];
					enemy[i] = nullptr;
				}

				// �����蔻��̊m�F
				if (IsHitCheck(player, enemy[i]))
				{
					player->SetActive(false);
					enemy[i]->Finalize();
					delete enemy[i];
					enemy[i] = nullptr;
					player->DecLife();
				}
			}
		}

		// �c�@��0�ɂȂ�ƃ��U���g��ʂɑJ�ڂ���
		if (player->GetLife() < 0)
		{
			return eSceneType::E_MINIGAME;
		}

		// �������Ԃ𒴂����烊�U���g�ɑJ�ڂ���
		if (ui->GetTimeFlg() == true)
		{
			return eSceneType::E_RESULT;
		}

    }
   

    return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw()const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	

	// �G�̕`��
	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//�v���C���[�̕`��
	player->Draw();

	// �|�[�Y�t���O�������Ă���ꍇ�̂݃|�[�Y�摜��`�悷��
	if (pause_flag)
	{
		DrawGraph(0, 0, pause_image, TRUE);
	}



	//�f�o�b�O�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Time:%f", timer);
	//���n�C�X�R�A�p
	DrawFormatString(0, 50, GetColor(255, 255, 255), "�n�C�X�R�A:%08d", score);
	//���X�s�[�h�p
	DrawFormatString(0, 100, GetColor(255, 255, 255), "�X�s�[�h:%08.1f", player->GetSpeed());
	//�����s�����p
	DrawFormatString(0, 150, GetColor(255, 255, 255), "���s����:%08d", mileage / 10);
	ui->Draw();
}



//�I��������
void GameMainScene::Finalize()
{
	

	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���\n");
	}

	//�X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);

	//���������Ɠ��_��ۑ�
	/*for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}*/

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;
	ui->Finalize();
	delete ui;

	for (int i = 0; i < 4; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	DeleteSoundMem(BGM);
	delete[] enemy;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene()const
{
	return eSceneType::E_MAIN;
}

int GameMainScene::GetScore()
{
	return score;
}


//�n�C�X�R�A�ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}


//�����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	//�v���C���[���o���A�𒣂��Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	//�G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (e == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}
