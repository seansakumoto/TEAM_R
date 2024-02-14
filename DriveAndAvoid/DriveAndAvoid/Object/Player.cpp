#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"


Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),invincible(0),reviv(0),
angle(0.0f),
						speed(0.0f), barrier_count(0),life(0),
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
	location = Vector2D(250.0f, 480.0f/5.0f*4);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 7.0f;//プレイヤーの速度デフォルト5
	barrier_count = 3;
	life = 3;

	//画像の読み込み
	image = LoadGraph("Resource/images/player.bmp");


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
		/*angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;*/
		if (barrier == nullptr)
		{
			barrier = new Barrier;
			invincible = 0;
			reviv = 30;
		}
	}


	//移動処理
	Movement();


	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		
	}

	//バリア処理
	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier = new Barrier;
		}
	}*/

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		invincible++;
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
			is_active = true;
		}
	}
}


//描画処理
void Player::Draw()
{
	////プレイヤー画像の描画
	//if (barrier != nullptr)
	//{
	//	if (invincible<reviv/2)
	//	{
	//		DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	//	}
	//	else
	//	{
	//		
	//	}
	//	if (invincible > reviv)
	//	{
	//		invincible = 0;
	//		reviv -= 4;
	//	}
	//}
	//else
	//{
	//	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	//}
	//DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, FALSE);
	

	DrawFormatString(550, 350, GetColor(0, 255, 0), "%d", life);
	DrawFormatString(550, 370, GetColor(255, 255, 255), "%f", location.x);

	////バリアが生成されていたら、描画を行う
	//if (barrier != nullptr)
	//{
	//	barrier->Draw(this->location);
	//}

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


void Player::DecLife()
{
	life--;
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


//残機取得処理
int Player::GetLife()const
{
	return life;
}


//バリアが有効か？を取得
bool Player::IsBarrier()const
{
	return (barrier != nullptr);
}


//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	float MoveSizeX = 100;
	float MoveSizeY = 480 / 5;
	angle = 0.0f;
	//
	//
	//Vector2D move = Vector2D(0.0f);
	//angle = 0.0f;

	////十字移動処理
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	//{
	//	move += Vector2D(-100.0f, 0.0f);
	//	angle = -DX_PI_F / 18;
	//}
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	//{
	//	move += Vector2D(100.0f, 0.0f);
	//	angle = DX_PI_F / 18;
	//}
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	//{
	//	move += Vector2D(0.0f, -150.0f);
	//}
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	//{
	//	move += Vector2D(0.0f, 150.0f);
	//}

	//location += move;


	////画面外に行かないように制限する
	//if ((location.x < 150.0f) || (location.x >= 640.0f - 180.0f) ||
	//	(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	//{
	//	location -= move;
	//}

 //   //スティックの入力を取得する
	//Vector2D stickInput = InputControl::GetLeftStick();

	//// スティックのX軸方向の入力に応じてプレイヤーキャラクターを移動させる
	//float moveSpeed = 6.0f; // 移動速度を設定する

	//float moveXAmount = stickInput.x * moveSpeed; // スティックの入力に応じて移動する量を計算 X
	//float moveYAmount = stickInput.y * moveSpeed; // Y

	//Vector2D move = Vector2D(moveXAmount, moveYAmount); // スティックの移動量

	//十字移動処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-MoveSizeX, 0.0f);
		angle = -DX_PI_F / 18;
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(MoveSizeX, 0.0f);
		angle = DX_PI_F / 18;
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -MoveSizeY);
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, MoveSizeY);
	}

	// プレイヤーキャラクターの位置を更新する
	location += move;

	//画面外に行かないように制限する
	if ((location.x <= 0.0f+box_size.x) || (location.x >= 500.0f) ||
		(location.y <=0.0f) || (location.y >= 480.0f))
	{
		location -= move;
	}

}


