#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),
                                          mileage(0), player(nullptr),
enemy(nullptr)
{
    
    for (int i = 0; i < 3; i++)
    {
        enemy_image[i] = NULL;
        enemy_count[i] = NULL;
    }
}


GameMainScene::~GameMainScene()
{
 

}

//初期化処理
void GameMainScene::Initialize()
{

   
    timer = 0;

    //高得点値を読み込む
    ReadHighScore();

    //画像の読み込み
    back_ground = LoadGraph("Resource/images/back.bmp");
    barrier_image = LoadGraph("Resource/images/barrier.png");
    int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120,
        enemy_image);

    //エラーチェック
    if (back_ground == -1)
    {
        throw("Resource/images/back.bmpがありません\n");
    }

    if (result == -1)
    {
        throw("Resource/images/car.bmpがありません\n");
    }

    if (barrier_image == -1)
    {
        throw("Resource/images/barrier.pngがありません\n");
    }

    //オブジェクトの生成
    player = new Player;
    ui = new UI;

    // オブジェクトの初期化
    player->Initialize();
    ui->Initialize();

    for (auto& e : enemy) {
        e->Initialize();
    }
}

//更新処理
eSceneType GameMainScene::Update()
{
    //プレイヤーの更新
    player->Update();
    ui->Update();

    //移動距離の更新
    mileage += (int)player->GetSpeed() + 5;

    //敵生成処理
    if (mileage / 20 % 100 == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (enemy[i] == nullptr)
            {
                int type = GetRand(3) % 3;
                enemy[i] = new Enemy(type, enemy_image[type]);
                enemy[i]->Initialize();
                break;
            }
        }
    }

    //敵の更新と当たり判定チェック
    for (int i = 0; i < 10; i++)
    {
        if (enemy[i] != nullptr)
        {
            enemy[i]->Updata(player->GetSpeed());

            //画面外に行ったら、敵を削除してスコア加算
            if (enemy[i]->GetLocation().y >= 640.0f)
            {
                enemy_count[enemy[i]->GetType()]++;
                enemy[i]->Finalize();
                delete enemy[i];
                enemy[i] = nullptr;
            }

            //当たり判定の確認
            if (IsHitCheck(player, enemy[i]))
            {
                player->SetActive(false);
                //player->DecreaseHp(-50.0f);
                enemy[i]->Finalize();
                delete enemy[i];
                enemy[i] = nullptr;
            }
        }
    }


    //制限時間を超えたらリザルトに遷移する
    if (ui->GetTimeFlg()==true)
    {
        return eSceneType::E_RESULT;
    }
    return GetNowScene();
}

//描画処理
void GameMainScene::Draw()const
{
    //背景画像の描画
    DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
    DrawGraph(0, mileage % 480, back_ground, TRUE);

    //敵の描画
    for (int i = 0; i < 10; i++)
    {
        if (enemy[i] != nullptr)
        {
            enemy[i]->Draw();
        }
    }

    //プレイヤーの描画
    player->Draw();
    
   

    //デバッグ用
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Time:%f",timer);
    //仮ハイスコア用
    DrawFormatString(0, 50, GetColor(255, 255, 255), "ハイスコア:%08d", high_score);
    //仮スピード用
     DrawFormatString(0, 100, GetColor(255, 255, 255), "スピード:%08.1f",player->GetSpeed());
     //仮走行距離用
     DrawFormatString(0, 150, GetColor(255, 255, 255), "走行距離:%08d", mileage / 10);
     ui->Draw();
}


//終了時処理
void GameMainScene::Finalize()
{
    //スコアを計算する
    int score = (mileage / 10 * 10);
    for (int i = 0; i < 3; i++)
    {
        score += (i + 1) * 50 * enemy_count[i];
    }

    //リザルトデータの書き込み
    FILE* fp = nullptr;
    //ファイルオープン
    errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

    //エラーチェック
    if (result != 0)
    {
        throw("Resource/dat/result_data.csvが開けません\n");
    }

    //スコアを保存
    fprintf(fp, "%d,\n", score);

    //避けた数と得点を保存
    for (int i = 0; i < 3; i++)
    {
        fprintf(fp, "%d,\n", enemy_count[i]);
    }

    //ファイルクローズ
    fclose(fp);

    //動的確保したオブジェクトを削除する
    player->Finalize();
    delete player;
    ui->Finalize();
    delete ui;
    //delete ui;
    for (auto& e : enemy) {
        e->Finalize();
        delete e;
    }

    //for (int i = 0; i < 10; i++)
    //{
    //    if (enemy[i] != nullptr)
    //    {
    //        enemy[i]->Finalize();
    //        delete enemy[i];
    //        enemy[i] = nullptr;
    //    }
    //}

    //delete[] enemy;
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene()const
{
    return eSceneType::E_MAIN;
}


//ハイスコア読み込み
void GameMainScene::ReadHighScore()
{
    RankingData data;
    data.Initialize();

    high_score = data.GetScore(0);

    data.Finalize();
}


//当たり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
    // プレイヤーがバリアを張っていたら、当たり判定を無視する
    if (p->IsBarrier())
    {
        return false;
    }

    // 敵情報がなければ、当たり判定を無視する
    if (e == nullptr)
    {   
        return false;
    }


    return false;
}


    //コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
    return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}