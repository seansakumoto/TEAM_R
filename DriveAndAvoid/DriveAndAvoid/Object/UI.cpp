#include "UI.h"
#include "DxLib.h"
#include "../Scene/GameMainScene.h"


UI::UI() 
{
	
}


UI::~UI()
{

}


//初期化処理
void UI::Initialize()
{
	cnt = 0;
	startcnt = 180;
	timeFlg = false;

	//画像の読み込み
	LoadDivGraph("Resource/images/number_r1.png", 10, 10, 1, 30, 60, Num); // 画像の分割読み込み

}



//更新処理
void UI::Update()
{
	
		++cnt;
		if (cnt >= 6000)
		{
			timeFlg = true;
		}

	

}


//描画処理
void UI::Draw()
{
	SetFontSize(50);
	DrawFormatString(510, 10, GetColor(0, 255, 0), "TIME");
	DrawGraph(530, 60, Num[(cnt % 10000) / 1000], TRUE);
	DrawGraph(560, 60, Num[(cnt % 1000) / 100], TRUE);
	/*DrawFormatString(520, 10, GetColor(0, 255, 0), "スコア");
	DrawGraph(520, 30,  , TRUE);*/
	//DrawFormatString(550, 350, GetColor(0, 255, 0), "%d", life);

}


//終了時処理
void UI::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

}

int UI::GetTimeFlg()
{
	return timeFlg;
}











