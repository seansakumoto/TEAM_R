#pragma once
#include "../Utility/Vector2D.h"

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

    Vector2D location;
    Vector2D box_size;
public:
    Enemy();
    ~Enemy();

    // �������󂯎��R���X�g���N�^�[
    Enemy(int initialX, int initialY);

    void Initialize();
    void Update();
    void Draw()const;
    void Finalize();

    int GetY() const; // Y���W���擾���郁�\�b�h

    Vector2D GetLocation() const;
    Vector2D GetBoxSize() const;
};