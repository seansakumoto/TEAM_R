#include "MiniGameScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <chrono>
#include <thread>

MiniGameScene::MiniGameScene()
{

}

MiniGameScene::~MiniGameScene()
{

}

// ����������
void MiniGameScene::Initialize()
{

}

// �X�V����
eSceneType MiniGameScene::Update()
{
	// �{�^���������ꂽ��F��ύX����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		DrawColoredBox(GetColor(255, 0, 0)); // �ԐF�̎l�p�`��`��
		return eSceneType::E_MAIN; // �Q�[�����C���V�[���Ɉړ�
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		DrawColoredBox(GetColor(255, 255, 0)); // ���F�̎l�p�`��`��
		return eSceneType::E_MAIN; // �Q�[�����C���V�[���Ɉړ�
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		DrawColoredBox(GetColor(0, 0, 255)); // �F�̎l�p�`��`��
		return eSceneType::E_MAIN; // �Q�[�����C���V�[���Ɉړ�
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		DrawColoredBox(GetColor(0, 255, 0)); // �ΐF�̎l�p�`��`��
		return eSceneType::E_MAIN; // �Q�[�����C���V�[���Ɉړ�
	}

	return GetNowScene();
}

// �`�揈��
void MiniGameScene::Draw() const
{
	static std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - startTime;

	if (elapsedTime.count() < 10.0) // 10�b�ԕ`����s��
	{
		// �F�̐ݒ�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h���[�h�̐ݒ�i�s�����j

		// ���F�̎l�p�`��`��
		DrawBox(100, 100, 200, 200, GetColor(255, 255, 0), TRUE);

		// �o�ߎ��Ԃ�\��
		int remainingTime = static_cast<int>(10.0 - elapsedTime.count());
		DrawFormatString(10, 10, GetColor(255, 255, 255), "Time: %d", remainingTime);
	}
	else
	{
		// 10�b���o�߂����牽���`�悵�Ȃ�
		ClearDrawScreen();
	}
}

// �I������
void MiniGameScene::Finalize()
{

}

// ���݂̃V�[�������擾
eSceneType MiniGameScene::GetNowScene() const
{
	return eSceneType::E_MINIGAME;
}

// �C�ӂ̐F�̎l�p�`��`�悷��
void MiniGameScene::DrawColoredBox(unsigned int color) const
{
	DrawBox(300, 300, 400, 400, color, TRUE);
}