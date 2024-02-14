#pragma once



class Enemy
{
private:

    // メンバー変数の宣言
    int x; // x座標
    int y; // y座標
    int width; // 幅
    int height; // 高さ
    int speed; // 移動速度

    int image;


public:
    Enemy();
    ~Enemy();

    // 引数を受け取るコンストラクター
    Enemy(int initialX, int initialY);

    void Initialize();
    void Update();
    void Draw()const;
    void Finalize();

    int GetX() const; // X座標を取得するメソッド
    int GetY() const; // Y座標を取得するメソッド
};