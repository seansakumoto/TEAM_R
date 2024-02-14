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

    // �������󂯎��R���X�g���N�^�[
    Enemy(int initialX, int initialY);

    void Initialize();
    void Update();
    void Draw()const;
    void Finalize();

    int GetX() const; // X���W���擾���郁�\�b�h
    int GetY() const; // Y���W���擾���郁�\�b�h
};