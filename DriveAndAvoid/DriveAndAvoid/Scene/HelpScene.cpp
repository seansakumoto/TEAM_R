#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() :background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}


//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Control.png");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images.Cntrol.pngがありません\n");
	}
}


//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//描画処理
void HelpScene::Draw()const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(16);
	DrawString(20, 100, "ヘルプ画面", 0xffffff, 0);


	DrawString(20, 140, "操作方法", 0xffffff, 0);
	DrawString(20, 180, "十字操作で移動", 0xffffff, 0);
	DrawString(20, 200, "STARTボタンでpause", 0xffffff, 0);

	
	DrawString(20, 240, "ゲームルール", 0xffffff, 0);
	DrawString(20, 280, "これは障害物を避けながら", 0xffffff, 0);
	DrawString(20, 300, "走り続けるゲームです", 0xffffff, 0);
	DrawString(20, 320, "燃料が尽きるか障害物に", 0xffffff, 0);
	DrawString(20, 340, "数回当たるとゲームオーバーです", 0xffffff, 0);

	DrawString(150, 450, "Bボタンを押してタイトルへ戻る", 0xffffff, 0);
}


//終了処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene()const
{
	return eSceneType::E_HELP;
}