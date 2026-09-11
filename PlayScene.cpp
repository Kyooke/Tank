#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
#include <vector>
//#include "TankHead.h"
namespace
{
	const int ENEMY_MAX = 5;
	int NOW_ENEMY = 1;
}
//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
	Instantiate<Enemy>(this);
	
}

void PlayScene::Update()
{
	Enemy* enemy;
	enemy->OnCollision();
	NOW_ENEMY += enemy;
	if (NOW_ENEMY < ENEMY_MAX)
	{
		float randX = rand() + transform_.position_.z;
		float randZ = rand() + transform_.position_.z;
		XMStringVecroe position = XMFLOAT3(randX, transform_.position_.y, randZ);
		Instantiate<Enemy>(this,position);

	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
