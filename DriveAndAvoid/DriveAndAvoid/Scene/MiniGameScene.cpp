#include "MiniGameScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

MiniGameScene::MiniGameScene() :background_image(NULL)
{

}



MiniGameScene::~MiniGameScene()
{

}

//初期化処理
void MiniGameScene::Initialize()
{
    // 画像の読み込み
    background_image = LoadGraph("Resource/images/backimage.png");
    background_image1 = LoadGraph("Resource/images/backimagehelp.png");

    // エラーチェック
    if (background_image == -1)
    {
        throw("Resource/images/backimagehelp.pngがありません\n");
    }

    if (background_image1 == -1)
    {
        throw("Resource/images/backimage.pngがありません\n");
    }
}


//更新処理
eSceneType MiniGameScene::Update()
{
    // Bボタンが押されたら、画像を切り替える
    if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
    {
        // 画像を切り替える
        if (currentImage == 0) {
            currentImage = 1;
        }
        else {
            currentImage = 0;
        }
    }

    // Aボタンが押されたら、タイトルに戻る
    if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
    {
        return eSceneType::E_MAIN;
    }

    return GetNowScene();
}


//描画処理
void MiniGameScene::Draw()const
{
    // 読み込んだ画像の表示
    if (currentImage == 0) {
        DrawGraph(0, 0, background_image, TRUE);
    }
    else {
        DrawGraph(0, 0, background_image1, TRUE);
    }
}

//終了処理
void MiniGameScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	
}

//現在のシーン情報を取得
eSceneType MiniGameScene::GetNowScene()const
{
	return eSceneType::E_MINIGAME;
}