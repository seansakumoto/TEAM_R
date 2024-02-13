#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"



Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
						speed(0.0f), barrier_count(0),
barrier(nullptr)
{

}


Player::~Player()
{
	
}


//初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(150.0f, 400.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 6.0f;//プレイヤーの速度デフォルト5
	barrier_count = 3;

	//画像の読み込み
	image = LoadGraph("Resource/images/car1pol.bmp");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}



//更新処理
void Player::Update()
{
	//操作不可状態であれば、自身を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}


	//移動処理
	Movement();


	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//バリア処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}


//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	DrawFormatString(400, 350, GetColor(255, 255, 255), "%f", location.x);
	DrawFormatString(400, 370, GetColor(255, 255, 255), "%f", location.y);

	// スティックの移動量を取得する
	Vector2D stickInput = InputControl::GetLeftStick();

	// スティックの移動量を表示する
	DrawFormatString(400, 390, GetColor(255, 255, 255), "Stick X: %f", stickInput.x);
	DrawFormatString(400, 410, GetColor(255, 255, 255), "Stick Y: %f", stickInput.y);


	//バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}


//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}


//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}


//位置情報取得処理
Vector2D Player::GetLocation()const
{
	return this->location;
}


//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}


//速さ取得処理
float Player::GetSpeed()const
{
	return this->speed;
}


//バリア枚数取得処理
int Player::GetBarrierCount()const
{
	return this->barrier_count;
}


//バリアが有効か？を取得
bool Player::IsBarrier()const
{
	return (barrier != nullptr);
}


//移動処理
void Player::Movement()
{
	
    //スティックの入力を取得する
	Vector2D stickInput = InputControl::GetLeftStick();

	// スティックのX軸方向の入力に応じてプレイヤーキャラクターを移動させる
	float moveSpeed = 6.0f; // 移動速度を設定する

	float moveXAmount = stickInput.x * moveSpeed; // スティックの入力に応じて移動する量を計算 X
	float moveYAmount = stickInput.y * moveSpeed; // Y

	Vector2D move = Vector2D(moveXAmount, moveYAmount); // スティックの移動量

	// 十字キーの入力を取得する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT)) {
		move.x -= 100.0f; // 十字キーの左入力に応じて移動する量を減らす
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT)) {
		move.x += 100.0f; // 十字キーの右入力に応じて移動する量を増やす
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP)) {
		move.y -= 150.0f; // 十字キーの上入力に応じて移動する量を減らす
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN)) {
		move.y += 150.0f; // 十字キーの下入力に応じて移動する量を増やす
	}

	// プレイヤーキャラクターの位置を更新する
	location += move;

	// 画面外に行かないように制限する
	if ((location.x < 150.0f) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y)) {
		location -= move;
	}

}


