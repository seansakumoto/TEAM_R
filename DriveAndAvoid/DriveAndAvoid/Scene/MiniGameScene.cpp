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

// 初期化処理
void MiniGameScene::Initialize()
{

}

// 更新処理
eSceneType MiniGameScene::Update()
{
	// ボタンが押されたら色を変更する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		DrawColoredBox(GetColor(255, 0, 0)); // 赤色の四角形を描画
		return eSceneType::E_MAIN; // ゲームメインシーンに移動
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		DrawColoredBox(GetColor(255, 255, 0)); // 黄色の四角形を描画
		return eSceneType::E_MAIN; // ゲームメインシーンに移動
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		DrawColoredBox(GetColor(0, 0, 255)); // 青色の四角形を描画
		return eSceneType::E_MAIN; // ゲームメインシーンに移動
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		DrawColoredBox(GetColor(0, 255, 0)); // 緑色の四角形を描画
		return eSceneType::E_MAIN; // ゲームメインシーンに移動
	}

	return GetNowScene();
}

// 描画処理
void MiniGameScene::Draw() const
{
	static std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - startTime;

	if (elapsedTime.count() < 10.0) // 10秒間描画を行う
	{
		// 色の設定
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードの設定（不透明）

		// 黄色の四角形を描画
		DrawBox(100, 100, 200, 200, GetColor(255, 255, 0), TRUE);

		// 経過時間を表示
		int remainingTime = static_cast<int>(10.0 - elapsedTime.count());
		DrawFormatString(10, 10, GetColor(255, 255, 255), "Time: %d", remainingTime);
	}
	else
	{
		// 10秒が経過したら何も描画しない
		ClearDrawScreen();
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

// 任意の色の四角形を描画する
void MiniGameScene::DrawColoredBox(unsigned int color) const
{
	DrawBox(300, 300, 400, 400, color, TRUE);
}