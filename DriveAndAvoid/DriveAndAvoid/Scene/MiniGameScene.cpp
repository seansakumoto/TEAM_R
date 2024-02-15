#include "MiniGameScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <chrono>
#include <thread>
#include <cstdlib> // 追加

MiniGameScene::MiniGameScene()
{
    SetFontSize(50);
    // 乱数のシード値を設定する
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

MiniGameScene::~MiniGameScene()
{

}

void MiniGameScene::Initialize()
{
    int image = LoadDivGraph("Resource/images/color.png", 4, 4, 1, 50, 50, color);

    // 読み込みエラーチェック
    if (image == -1)
    {
        throw("画像の読み込みに失敗しました");
    }

    // 画像の表示位置を初期化
    for (int i = 0; i < 10; ++i)
    {
        // 画面内に収まるように画像の位置を調整
        while (true)
        {
            // 画像の位置をランダムに決定
            imagePositions[i].x = rand() % (600 - 50); // x座標をランダムに生成（画像の幅を考慮）
            imagePositions[i].y = rand() % (400 - 50); // y座標をランダムに生成（画像の高さを考慮）

            // 重なりをチェック
            bool overlap = false;
            for (int j = 0; j < i; ++j)
            {
                if (abs(imagePositions[i].x - imagePositions[j].x) < 50 && abs(imagePositions[i].y - imagePositions[j].y) < 50)
                {
                    overlap = true;
                    break;
                }
            }

            // 重なりがなければループを抜ける
            if (!overlap)
            {
                break;
            }
        }
    }

    // ビルドシーンが切り替わるたびにランダムな画像のインデックスを決定
    currentImageIndex = std::vector<int>(10); // 要素数10のvectorを初期化
    for (int i = 0; i < 10; ++i)
    {
        currentImageIndex[i] = rand() % 4; // 0から3までのランダムな数を生成
    }
}



// 更新処理
eSceneType MiniGameScene::Update()
{
    // 画像の位置をランダムに移動させる
    for (int i = 0; i < 10; ++i)
    {
        // 画像の位置を少しランダムに変更
        imagePositions[i].x += (rand() % 11) - 5; // -5から5までのランダムな数を加える
        imagePositions[i].y += (rand() % 11) - 5; // -5から5までのランダムな数を加える

        // 画像が画面外に出ないようにする
        if (imagePositions[i].x < 0) imagePositions[i].x = 0;
        if (imagePositions[i].x > (600 - 50)) imagePositions[i].x = 600 - 50;
        if (imagePositions[i].y < 0) imagePositions[i].y = 0;
        if (imagePositions[i].y > (400 - 50)) imagePositions[i].y = 400 - 50;
    }

    return GetNowScene();
}

// 描画処理
void MiniGameScene::Draw() const
{

    // 画面をクリア
    ClearDrawScreen();

    // 固定された位置にランダムな画像を表示
    for (int i = 0; i < 10; ++i)
    {
        DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // 画像を表示
    }
    // 画面を更新
    ScreenFlip();
}

// 終了処理
void MiniGameScene::Finalize()
{

}

// 現在のシーン情報を取得
eSceneType MiniGameScene::GetNowScene() const
{
    return eSceneType::E_MINIGAME;
}