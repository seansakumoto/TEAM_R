#include "CreditScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

CreditScene::CreditScene():back_image(NULL)
{

}

CreditScene::~CreditScene()
{

}


//初期化処理
void CreditScene::Initialize()
{
	back_image = LoadGraph("Resource/images/Credit_back_image.png");

	if (back_image == -1)
	{
		throw("Credit_back_image.pngがありません");
	}
}


//更新処理
eSceneType CreditScene::Update()
{
	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}


//描画処理
void CreditScene::Draw()const
{
	DrawGraph(0, 0, back_image, TRUE);

	//音声提供者様紹介
	DrawFormatString(25, 100, GetColor(255,0,255), "音声素材提供元");
	DrawFormatString(25, 140, GetColor(255,255,255), "Pocketsound(https://pocket-se.info/)");
	DrawFormatString(25, 160, GetColor(255,255,255), "魔王魂(https://maou.audio/)");
	DrawFormatString(25, 180, GetColor(255, 255, 255), "効果音ラボ(https://soundeffect-lab.info/)");
	DrawFormatString(25, 200, GetColor(255, 255, 255), "DOVA-SYNDROME(https://dova-s.jp/)");
	
	//画像提供者様紹介
	DrawFormatString(25, 300, GetColor(255, 0, 255),"画像素材提供元");
	DrawFormatString(25, 320, GetColor(255, 255, 255), "ぱわぽすけ(https://pawaposuke.com/)");
	DrawFormatString(25, 340, GetColor(255, 255, 255), "いらすとや(https://www.irasutoya.com/)");
}


//終了時処理
void CreditScene::Finalize()
{
	DeleteGraph(back_image);
}


//現在のシーン情報を取得
eSceneType CreditScene::GetNowScene()const
{
	return eSceneType::E_CREDIT;
}


