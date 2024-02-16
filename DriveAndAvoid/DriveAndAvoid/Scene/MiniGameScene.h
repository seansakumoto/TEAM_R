#pragma once

#include "SceneBase.h"
#include "DxLib.h" // DxLib�̃w�b�_�t�@�C�����C���N���[�h
#include <chrono>
#include <vector> // std::vector���g�p���邽�߂ɒǉ�


class MiniGameScene : public SceneBase
{
private:
    int background_image; // �w�i�摜
    int background_image1; // �w�i�摜2
    int remainingLives; // �v���C���[�̎c�@
    // �����Ƀ����o�ϐ���錾
    // DxLib�Œ񋟂���Ă���VECTOR2D�\���̂��g��
    std::vector<VECTOR> imagePositions; // �摜�̕\���ʒu
    int color[4]; // �摜�̐F

    std::vector<int> currentImageIndex; // ���݂̉摜�̃C���f�b�N�X��ێ�����z��

    std::chrono::time_point<std::chrono::system_clock> startTime; // �J�n����

    int bakuhatu;

    int BGM;
    int BGM2;
    int help;

    int showHelp;
    int showImage;
public:
    MiniGameScene();
    virtual ~MiniGameScene();

    virtual void Initialize() override;
    virtual eSceneType Update() override;
    virtual void Draw() const override;
    virtual void Finalize() override;
    void HideImageByButton(int buttonIndex);

    void DrawBackground() const;

 

    virtual eSceneType GetNowScene() const override;
};