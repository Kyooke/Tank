#include "Enemy.h"
#include"Engine//Model.h"
#include "Ground.h"
#include "Engine//SphereCollider.h"

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
	data.start.y = 0.0f;//地面は0より下に掘られて作られている。そうじゃないときはもっと上から！
	data.dir = { 0,-1,0 };//真下にレイを飛ばす

	Ground* pGround = (Ground*)FindObject("Ground");
	int hGroundModel = pGround->GetModelHandle();
	Model::RayCast(hGroundModel, &data);
	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
		//レイの発射一から、地面までの距離を引いて、地面をぴったりつける
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

int Enemy::OnCollision()
{
	KillMe();
	 return -1;
}
