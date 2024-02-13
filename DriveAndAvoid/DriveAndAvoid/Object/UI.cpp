#include "UI.h"
#include "DxLib.h"


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
	timeFlg = false;

	//画像の読み込み
	LoadDivGraph("Resource/images/Number_r.bmp", 10, 10, 1, 20, 30, Num); // 画像の分割読み込み
	////エラーチェック
	//if (.../)
	//{
	//	throw(".../");
	//}
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
	DrawGraph(0, 25, Num[(cnt % 10000) / 1000], TRUE);
	DrawGraph(20, 25, Num[(cnt % 1000) / 100], TRUE);

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











