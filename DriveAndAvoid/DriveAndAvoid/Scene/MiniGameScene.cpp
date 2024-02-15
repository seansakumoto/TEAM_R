	#include "MiniGameScene.h"
	#include "../Utility/InputControl.h"
	#include "DxLib.h"
	#include <chrono>
	#include <cstdlib> 
	#include <sstream> 
	#include <iomanip> 

	MiniGameScene::MiniGameScene() 
	{
		// �����̃V�[�h�l��ݒ肷��
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// BGM��ǂݍ���
		BGM = LoadSoundMem("Resource/sounds/goe.mp3");
		BGM2 = LoadSoundMem("Resource/sounds/ok.mp3");

		// BGM�����[�v�Đ�����
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
	}

	MiniGameScene::~MiniGameScene()
	{
		// BGM�̉��
		DeleteSoundMem(BGM);
	}

	void MiniGameScene::Initialize()
	{
		 
		help = LoadGraph("Resource/images/helpimage1.png");

		// �摜��ǂݍ���
		int image = LoadDivGraph("Resource/images/color.png", 4, 4, 1, 50, 50, color);

		bakuhatu = LoadGraph("Resource/images/bakuhatu.png");

		// �ǂݍ��݃G���[�`�F�b�N
		if (image == -1 || bakuhatu == -1)
		{
			throw("�摜�̓ǂݍ��݂Ɏ��s���܂���");
		}

		// �摜�̕\���ʒu��������
		int numImages = rand() % 31 + 20; // 10����30�܂ł̃����_���Ȑ��𐶐�
		imagePositions.resize(numImages); // std::vector�̃T�C�Y��ݒ�
		currentImageIndex.resize(numImages); // �摜�̃C���f�b�N�X��ݒ�
		for (int i = 0; i < numImages; ++i)
		{
			// ��ʓ��Ɏ��܂�悤�ɉ摜�̈ʒu�𒲐�
			while (true)
			{
				// �摜�̈ʒu�������_���Ɍ���
				imagePositions[i].x = rand() % (600 - 50); // x���W�������_���ɐ����i�摜�̕����l���j
				imagePositions[i].y = rand() % (400 - 50); // y���W�������_���ɐ����i�摜�̍������l���j

				// �d�Ȃ���`�F�b�N
				bool overlap = false;
				for (int j = 0; j < i; ++j)
				{
					if (abs(imagePositions[i].x - imagePositions[j].x) < 50 && abs(imagePositions[i].y - imagePositions[j].y) < 50)
					{
						overlap = true;
						break;
					}
				}

				// �d�Ȃ肪�Ȃ���΃��[�v�𔲂���
				if (!overlap)
				{
					break;
				}
			}

			// �摜�̃C���f�b�N�X��ݒ�
			currentImageIndex[i] = rand() % 4;
		}

		// �������Ԃ�ݒ�
		startTime = std::chrono::system_clock::now();


	}

	// �X�V����
	eSceneType MiniGameScene::Update()
	{

		// �{�^���̏�Ԃ��擾
		bool buttonB = InputControl::GetButtonDown(XINPUT_BUTTON_B);
		bool buttonX = InputControl::GetButtonDown(XINPUT_BUTTON_X);
		bool buttonA = InputControl::GetButtonDown(XINPUT_BUTTON_A);
		bool buttonY = InputControl::GetButtonDown(XINPUT_BUTTON_Y);

		// �e�{�^���������ꂽ���ǂ������m�F���A�Y������摜��1����\���ɂ���
		if (buttonB)
		{
			HideImageByButton(0);
		}
		if (buttonX)
		{
			HideImageByButton(1);
		}
		if (buttonA)
		{
			HideImageByButton(2);
		}
		if (buttonY)
		{
			HideImageByButton(3);
		}

		// �摜�̈ʒu�������_���Ɉړ�������
		int numImages = static_cast<int>(imagePositions.size());
		for (int i = 0; i < numImages; ++i)
		{
			// �摜�̈ʒu�����������_���ɕύX
			imagePositions[i].x += (rand() % 11) - 5; // -5����5�܂ł̃����_���Ȑ���������
			imagePositions[i].y += (rand() % 11) - 5; // -5����5�܂ł̃����_���Ȑ���������

			// �摜����ʊO�ɏo�Ȃ��悤�ɂ���
			if (imagePositions[i].x < 0) imagePositions[i].x = 0;
			if (imagePositions[i].x > (600 - 50)) imagePositions[i].x = 600 - 50;
			if (imagePositions[i].y < 0) imagePositions[i].y = 0;
			if (imagePositions[i].y > (400 - 50)) imagePositions[i].y = 400 - 50;
		}

		// ��ʂ��N���A
		ClearDrawScreen();

		// �Œ肳�ꂽ�ʒu�Ƀ����_���ȉ摜��\��
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] != -1)
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // �摜��\��
			}
			else
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, bakuhatu, TRUE); // �����摜��\��
			}
		}

		// ��ʂ��X�V
		ScreenFlip();

		// �Œ肳�ꂽ�ʒu�Ƀ����_���ȉ摜��\��
		bool allImagesHidden = true; // ���ׂẲ摜����\�����ǂ����������t���O
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] != -1)
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // �摜��\��
				allImagesHidden = false; // ��ł��\������Ă���摜������΃t���O��false�ɂ���
			}
			else
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, bakuhatu, TRUE); // �����摜��\��
			}
		}

		// ��ʂ��X�V
		ScreenFlip();

		// ���ׂẲ摜����\���ɂȂ����ꍇ��E_END��Ԃ�
		if (allImagesHidden) {
			return eSceneType::E_TITLE;
		}

		// 10�b�o�߂��Ă��Ȃ��ꍇ�͂܂����̃V�[���𑱂���
		return GetNowScene();
	}

	// �`�揈��
	void MiniGameScene::Draw() const
	{
		// ��ʂ��N���A
		ClearDrawScreen();

	

		// �Œ肳�ꂽ�ʒu�Ƀ����_���ȉ摜��\��
		int numImages = static_cast<int>(imagePositions.size());
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] != -1)
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // �摜��\��
			}
			else
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, bakuhatu, TRUE); // �����摜��\��
			}
		}

		// ��ʂ��X�V
		ScreenFlip();

	}

	// �{�^���ɉ����ĉ摜���\���ɂ���֐�
	void MiniGameScene::HideImageByButton(int buttonIndex)
	{
		// ���ׂẲ摜�𒲂ׂāA�Ή�����{�^���ƈ�v����摜������΍ŏ���1������\���ɂ���
		int numImages = static_cast<int>(imagePositions.size());
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] == buttonIndex)
			{
				// �{�^���ɑΉ�����摜�����������ꍇ�́A���̉摜�̃C���f�b�N�X�����������邱�ƂŔ�\���ɂ���
				// �܂��A�Ή�����SE���Đ�����
				PlaySoundMem(BGM2, DX_PLAYTYPE_BACK);
				currentImageIndex[i] = -1;
				break; // �ŏ���1������\���ɂ��邽�߁A���������烋�[�v�𔲂���
			}
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

