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

    void Initialize();
    void Updata();
    void Draw()const;
    void Finalize();

};