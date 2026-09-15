#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
#include <cstdlib>

namespace
{
	const int ENEMY_MAX = 5;
	int nowEnemyCount = 1; 
}

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

	if (nowEnemyCount < ENEMY_MAX)
	{
		Enemy* newEnemy = Instantiate<Enemy>(this);

		float randX = static_cast<float>((rand() % 40) - 20); // -20 〜 20
		float randZ = static_cast<float>((rand() % 40) - 20); // -20 〜 20
		XMFLOAT3 pos = XMFLOAT3(randX, 0.0f, randZ);

		newEnemy->SetPosition(pos);

		nowEnemyCount++;
	}
}

void PlayScene::DecreaseEnemyCount()
{
	if (nowEnemyCount > 0)
	{
		nowEnemyCount--;
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}