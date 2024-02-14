#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>

#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),
mileage(0), player(nullptr),
enemy(nullptr)
{

    for (int i = 0; i < 3; i++)
    {
        image = NULL;
        image = NULL;
    }
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
    timer = 0;

    //�����_�l��ǂݍ���
    ReadHighScore();

    //�摜�̓ǂݍ���
    back_ground = LoadGraph("Resource/images/back.bmp");
    barrier_image = LoadGraph("Resource/images/barrier.png");
    //int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
    // 
    // LoadGraph�œG�̉摜��ǂݍ���
    //image = LoadGraph("Resource/images/barikedo1.png");
    image = LoadGraph("Resource/images/barikedo.png");


    //�G���[�`�F�b�N
    if (back_ground == -1)
    {
        throw("Resource/images/back.bmp������܂���\n");
    }

    /*  if (result == -1)
      {
          throw("Resource/images/car.bmp������܂���\n");
      }*/

    if (barrier_image == -1)
    {
        throw("Resource/images/barrier.png������܂���\n");
    }

    if (image == -1)
    {
        throw("Resource/images/barikedo.png������܂���\n");
    }

    //�I�u�W�F�N�g�̐���
    player = new Player;
    enemy = new Enemy * [10];
    ui = new UI;

    //�I�u�W�F�N�g�̏�����
    player->Initialize();
    ui->Initialize();

    for (int i = 0; i < 10; i++)
    {
        enemy[i] = nullptr;
    }

}

//�X�V����
eSceneType GameMainScene::Update()
{
    //�v���C���[�̍X�V
    player->Update();
    ui->Update();

    //�ړ������̍X�V
    mileage += (int)player->GetSpeed() + 5;
    // �G��������
    if (mileage / 20 % 100 == 0)
    {
        for (int i = 0; i < 10; i++)
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
    for (int i = 0; i < 10; i++)
    {
        if (enemy[i] != nullptr)
        {
            enemy[i]->Updata(player->GetSpeed());

            // ��ʊO�ɍs������A�G���폜���ăX�R�A���Z
            if (enemy[i]->GetLocation().y >= 640.0f)
            {
                enemy_count[enemy[i]->GetType()]++;
                enemy[i]->Finalize();
                delete enemy[i];
                enemy[i] = nullptr;
            }

            // �����蔻��̊m�F
            if (IsHitCheck(player, enemy[i]))
            {
                player->SetActive(false);
                // player->DecreaseHp(-50.0f);
                enemy[i]->Finalize();
                delete enemy[i];
                enemy[i] = nullptr;
            }
        }
    }

    //�������Ԃ𒴂����烊�U���g�ɑJ�ڂ���
    if (ui->GetTimeFlg() == true)
    {
        return eSceneType::E_RESULT;
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
    for (int i = 0; i < 10; i++)
    {
        if (enemy[i] != nullptr)
        {
            enemy[i]->Draw();
        }
    }

    //�v���C���[�̕`��
    player->Draw();



    //�f�o�b�O�p
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Time:%f", timer);
    //���n�C�X�R�A�p
    DrawFormatString(0, 50, GetColor(255, 255, 255), "�n�C�X�R�A:%08d", high_score);
    //���X�s�[�h�p
    DrawFormatString(0, 100, GetColor(255, 255, 255), "�X�s�[�h:%08.1f", player->GetSpeed());
    //�����s�����p
    DrawFormatString(0, 150, GetColor(255, 255, 255), "���s����:%08d", mileage / 10);
    ui->Draw();
}



//�I��������
void GameMainScene::Finalize()
{
    //�X�R�A���v�Z����
    int score = (mileage / 10 * 10);
    for (int i = 0; i < 3; i++)
    {
        score += (i + 1) * 50 * enemy_count[i];
    }

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
    for (int i = 0; i < 3; i++)
    {
        fprintf(fp, "%d,\n", enemy_count[i]);
    }

    //�t�@�C���N���[�Y
    fclose(fp);

    //���I�m�ۂ����I�u�W�F�N�g���폜����
    player->Finalize();
    delete player;
    ui->Finalize();
    delete ui;

    for (int i = 0; i < 10; i++)
    {
        if (enemy[i] != nullptr)
        {
            enemy[i]->Finalize();
            delete enemy[i];
            enemy[i] = nullptr;
        }
    }

    delete[] enemy;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene()const
{
    return eSceneType::E_MAIN;
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