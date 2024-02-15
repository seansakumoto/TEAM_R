	#include "MiniGameScene.h"
	#include "../Utility/InputControl.h"
	#include "DxLib.h"
	#include <chrono>
	#include <cstdlib> 
	#include <sstream> 
	#include <iomanip> 

	MiniGameScene::MiniGameScene() 
	{
		// 乱数のシード値を設定する
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// BGMを読み込む
		BGM = LoadSoundMem("Resource/sounds/goe.mp3");

		// BGMをループ再生する
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
	}

	MiniGameScene::~MiniGameScene()
	{
		// BGMの解放
		DeleteSoundMem(BGM);
	}

	void MiniGameScene::Initialize()
	{
		 
		help = LoadGraph("Resource/images/helpimage1.png");

		// 画像を読み込む
		int image = LoadDivGraph("Resource/images/color.png", 4, 4, 1, 50, 50, color);

		bakuhatu = LoadGraph("Resource/images/bakuhatu.png");

		// 読み込みエラーチェック
		if (image == -1 || bakuhatu == -1)
		{
			throw("画像の読み込みに失敗しました");
		}

		// 画像の表示位置を初期化
		int numImages = rand() % 21 + 10; // 10から30までのランダムな数を生成
		imagePositions.resize(numImages); // std::vectorのサイズを設定
		currentImageIndex.resize(numImages); // 画像のインデックスを設定
		for (int i = 0; i < numImages; ++i)
		{
			// 画面内に収まるように画像の位置を調整
			while (true)
			{
				// 画像の位置をランダムに決定
				imagePositions[i].x = rand() % (600 - 50); // x座標をランダムに生成（画像の幅を考慮）
				imagePositions[i].y = rand() % (400 - 50); // y座標をランダムに生成（画像の高さを考慮）

				// 重なりをチェック
				bool overlap = false;
				for (int j = 0; j < i; ++j)
				{
					if (abs(imagePositions[i].x - imagePositions[j].x) < 50 && abs(imagePositions[i].y - imagePositions[j].y) < 50)
					{
						overlap = true;
						break;
					}
				}

				// 重なりがなければループを抜ける
				if (!overlap)
				{
					break;
				}
			}

			// 画像のインデックスを設定
			currentImageIndex[i] = rand() % 4;
		}

		// 制限時間を設定
		startTime = std::chrono::system_clock::now();


	}

	// 更新処理
	eSceneType MiniGameScene::Update()
	{
	

		// 残り時間を計算
		auto currentTime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
		double remainingTime = 10.0 - elapsedSeconds.count();

		if (remainingTime <= 0) {
			// 残り時間が0以下になったらゲームメインに移動し、画像を全て非表示にする
			for (int i = 0; i < currentImageIndex.size(); ++i) {
				currentImageIndex[i] = -1; // 画像を非表示にする
			}
			return eSceneType::E_END;
		}


		// ボタンの状態を取得
		bool buttonB = InputControl::GetButtonDown(XINPUT_BUTTON_B);
		bool buttonX = InputControl::GetButtonDown(XINPUT_BUTTON_X);
		bool buttonA = InputControl::GetButtonDown(XINPUT_BUTTON_A);
		bool buttonY = InputControl::GetButtonDown(XINPUT_BUTTON_Y);

		// 各ボタンが押されたかどうかを確認し、該当する画像を1個ずつ非表示にする
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

		// 画像の位置をランダムに移動させる
		int numImages = static_cast<int>(imagePositions.size());
		for (int i = 0; i < numImages; ++i)
		{
			// 画像の位置を少しランダムに変更
			imagePositions[i].x += (rand() % 11) - 5; // -5から5までのランダムな数を加える
			imagePositions[i].y += (rand() % 11) - 5; // -5から5までのランダムな数を加える

			// 画像が画面外に出ないようにする
			if (imagePositions[i].x < 0) imagePositions[i].x = 0;
			if (imagePositions[i].x > (600 - 50)) imagePositions[i].x = 600 - 50;
			if (imagePositions[i].y < 0) imagePositions[i].y = 0;
			if (imagePositions[i].y > (400 - 50)) imagePositions[i].y = 400 - 50;
		}

		// 画面をクリア
		ClearDrawScreen();

		// 固定された位置にランダムな画像を表示
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] != -1)
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // 画像を表示
			}
			else
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, bakuhatu, TRUE); // 爆発画像を表示
			}
		}

		// 画面を更新
		ScreenFlip();



		// 10秒経過していない場合はまだこのシーンを続ける
		return GetNowScene();
	}

	// 描画処理
	void MiniGameScene::Draw() const
	{
		// 画面をクリア
		ClearDrawScreen();

	

		// 固定された位置にランダムな画像を表示
		int numImages = static_cast<int>(imagePositions.size());
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] != -1)
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, color[currentImageIndex[i]], TRUE); // 画像を表示
			}
			else
			{
				DrawGraph(imagePositions[i].x, imagePositions[i].y, bakuhatu, TRUE); // 爆発画像を表示
			}
		}

		// 画面を更新
		ScreenFlip();

	}

	// ボタンに応じて画像を非表示にする関数
	void MiniGameScene::HideImageByButton(int buttonIndex)
	{
		// すべての画像を調べて、対応するボタンと一致する画像があれば最初の1つだけ非表示にする
		int numImages = static_cast<int>(imagePositions.size());
		for (int i = 0; i < numImages; ++i)
		{
			if (currentImageIndex[i] == buttonIndex)
			{
				// ボタンに対応する画像が見つかった場合は、その画像のインデックスを初期化することで非表示にする
				currentImageIndex[i] = -1;
				break; // 最初の1つだけ非表示にするため、見つかったらループを抜ける
			}
		}
	}

	// 終了処理
	void MiniGameScene::Finalize()
	{

	}




	// 現在のシーン情報を取得
	eSceneType MiniGameScene::GetNowScene() const
	{
		return eSceneType::E_MINIGAME;
	}

