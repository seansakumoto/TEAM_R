#include "Enemy.h"
#include "DxLib.h"
#include"../Utility/InputControl.h"
#include"../Scene/GameMainScene.h"
#include <string>

Enemy::Enemy() : location(0.0f), box_size(0.0f) 
{

}


Enemy::~Enemy()
{
   
}

void Enemy::Initialize()
{
    // 障害物の画像を読み込む
    image = LoadGraph("Resource/images/bariked.png");
    // 初期位置をランダムに設定する
    int xPositions[] = { 15, 115, 215, 315, 415 };
    x = xPositions[GetRand(5)];

    y = 0; // 画面の上端から障害物を配置する

    // 移動速度を設定する
    speed = 5; // 移動速度（任意の値）

    // 障害物のサイズを設定する
    width = 75; // 障害物の幅
    height = 75; // 障害物の高さ

    // 位置や当たり判定の大きさを設定する
    location = Vector2D(x, y);
    box_size = Vector2D(width, height);
}

void Enemy::Update()
{
    // 障害物の移動処理
    y += speed; // y座標を下方向に移動する

    // 障害物が画面外に出たら再配置する
    if (y > 500) {
        // 初期位置を再設定する
        int xPositions[] = { 15, 115, 215, 315, 415 };
        x = xPositions[GetRand(5)];
        y = 0; // 画面の上端から再配置する
    }
}

void Enemy::Draw() const
{
    // 障害物の画像を描画する
    DrawGraph(x, y, image, TRUE);

}

void Enemy::Finalize()
{
    // リソースの解放などの終了処理を行う
    DeleteGraph(image);
}

int Enemy::GetY() const {
    return y;
}


// 引数を受け取るコンストラクターの実装
Enemy::Enemy(int initialX, int initialY) : x(initialX), y(initialY)
{
    // 引数で受け取った値を使った初期化処理
}

Vector2D Enemy::GetLocation() const {
    return location;
}

Vector2D Enemy::GetBoxSize() const {
    return box_size;
}