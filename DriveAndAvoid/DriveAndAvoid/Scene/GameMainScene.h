#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/UI.h"
#include"MiniGameScene.h"


class GameMainScene : public SceneBase
{
private:
    int high_score;         // ハイスコア
    int back_ground;        // 背景画像
    int pause_image;        //ポーズ画像
    int barrier_image;      // バリア映像
    int mileage;            // 走行距離
    int pause;
    //int enemy_image[3];     // 敵画像
    int image;              // 新しく追加した変数
    int enemy_count[3];     // 通り過ぎた敵カウント
    int BGM;
    float timer;
    bool pause_flag;        //ポーズ
    Player* player;         // プレイヤー
    Enemy** enemy;          // 敵
    UI* ui;


    // BGMが再生中かどうかを示すフラグ
    bool isBGMPlaying = false;


    
public:
    GameMainScene();
    virtual ~GameMainScene();

    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;

    virtual eSceneType GetNowScene() const override;

private:
    // ハイスコア読み込み処理
    void ReadHighScore();
    // 当たり判定
    bool IsHitCheck(Player* p, Enemy* e);
};