#pragma once

#include "SceneBase.h"
#include "DxLib.h" // DxLibのヘッダファイルをインクルード
#include <chrono>
#include <vector> // std::vectorを使用するために追加

class MiniGameScene : public SceneBase
{
private:
    int background_image; // 背景画像
    int background_image1; // 背景画像2

    // ここにメンバ変数を宣言
    // DxLibで提供されているVECTOR2D構造体を使う
    VECTOR imagePositions[10]; // 画像の表示位置
    int color[4]; // 画像の色

    std::vector<int> currentImageIndex; // 現在の画像のインデックスを保持する配列

    std::chrono::time_point<std::chrono::system_clock> startTime; // 開始時刻

public:
    MiniGameScene();
    virtual ~MiniGameScene();

    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;


    virtual eSceneType GetNowScene() const override;
};