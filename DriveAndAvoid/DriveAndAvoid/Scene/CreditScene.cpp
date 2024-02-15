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
	DrawFormatString(0, 0, GetColor(0, 255, 0), "クレジット表記\n");
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


