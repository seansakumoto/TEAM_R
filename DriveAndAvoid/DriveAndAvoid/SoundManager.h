#pragma once
#include"DxLib.h"

#define SOUND_NUM 100	//効果音の数

//#define PLAYER_ATTACK_SOUND  0    //プレイヤーの足音


//使用する音源のパス一覧（上のファイルほど再生優先度が高い）
static char sound_filepath[SOUND_NUM][256] =
{
	//"resource/sounds/通常攻撃.mp3",
};
struct Sound {
	int dat;		//サウンド格納用変数
	int num;		//優先順位
	bool play_flg;	//再生中かどうか
};
class SoundManager
{
private:
	static Sound sound_data[SOUND_NUM];
	static int now_play_sound;	//何番目の音が再生中か

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
		// 指定されたサウンドを停止する
		StopSoundMem(sound_data[_num].dat);
		sound_data[_num].play_flg = false;

	}
};
