#pragma once



class Enemy
{
private:

    // �����o�[�ϐ��̐錾
    int x; // x���W
    int y; // y���W
    int width; // ��
    int height; // ����
    int speed; // �ړ����x

    int image;


public:
    Enemy();
    ~Enemy();

    void Initialize();
    void Updata();
    void Draw()const;
    void Finalize();

};