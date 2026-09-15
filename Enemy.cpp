#include "Enemy.h"
#include "Engine//Model.h"
#include "Ground.h"
#include "Engine//SphereCollider.h"
#include "PlayScene.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	Model::SetAnimFrame(hModel_, 1, 100, 1.0f);
	Collider* collider = new SphereCollider({ 0,0,0 }, 0.5f);
	AddCollider(collider);
}

void Enemy::Update()
{
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;
	data.dir = { 0,-1,0 };

	Ground* pGround = (Ground*)FindObject("Ground");
	if (pGround != nullptr)
	{
		int hGroundModel = pGround->GetModelHandle();
		Model::RayCast(hGroundModel, &data);
		if (data.hit == true)
		{
			transform_.position_.y = -data.dist;
		}
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget != nullptr && pTarget->GetObjectName() == "Bullet")
	{
		pTarget->KillMe();

		KillMe();

		PlayScene* pScene = (PlayScene*)FindObject("PlayScene");
		if (pScene != nullptr)
		{
			pScene->DecreaseEnemyCount();
		}
	}
}