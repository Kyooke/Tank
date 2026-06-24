#include "TankHead.h"
#include "Engine//Model.h"
#include"assert.h"
#include "Tank.h"
#include"Engine//Camera.h"
#include "Engine//Input.h"
#include "Bullet.h"

TankHead::TankHead(GameObject* parent)
	: GameObject(parent, "Tank"), hModel_(-1)
{

}


void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
}

void TankHead::Update()
{
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 1.0f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		const float BULLET_SPPED  = 0.2f;
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = vTop - vRoot;
		vMove = vMove * BULLET_SPPED;
		XMFLOAT3 Move;
		XMStoreFloat3(&Move,vMove);



		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		pBullet->SetMoveVector(Move);
		pBullet->SetPosition(cannonTop);
	}
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
