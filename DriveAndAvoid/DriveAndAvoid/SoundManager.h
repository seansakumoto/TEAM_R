#pragma once
#include"DxLib.h"

#define SOUND_NUM 100	//���ʉ��̐�

//#define PLAYER_ATTACK_SOUND  0    //�v���C���[�̑���


//�g�p���鉹���̃p�X�ꗗ�i��̃t�@�C���قǍĐ��D��x�������j
static char sound_filepath[SOUND_NUM][256] =
{
	//"resource/sounds/�ʏ�U��.mp3",
};
struct Sound {
	int dat;		//�T�E���h�i�[�p�ϐ�
	int num;		//�D�揇��
	bool play_flg;	//�Đ������ǂ���
};
class SoundManager
{
private:
	static Sound sound_data[SOUND_NUM];
	static int now_play_sound;	//���Ԗڂ̉����Đ�����

public:
	static void LoadSound()
	{
		now_play_sound = SOUND_NUM;
		for (int i = 0; i < SOUND_NUM; i++)
		{
			sound_data[i].dat = LoadSoundMem(sound_filepath[i]);
			sound_data[i].num = i;
			sound_data[i].play_flg = false;
		}
	}
	static void DeleteSound()
	{
		for (int i = 0; i < SOUND_NUM; i++)
		{
			DeleteSoundMem(sound_data[i].dat);
		}
	}
	static void StartSound(int _num)
	{
		if (CheckSoundMem(sound_data[_num].dat) == false) {
			PlaySoundMem(sound_data[_num].dat, DX_PLAYTYPE_BACK);
		}
	}
	static void StopSound(int _num)
	{
		// �w�肳�ꂽ�T�E���h���~����
		StopSoundMem(sound_data[_num].dat);
		sound_data[_num].play_flg = false;

	}
};
