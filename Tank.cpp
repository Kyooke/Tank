#include "Tank.h"
#include "Engine//Model.h"
#include"Engine//Input.h"
#include "Engine//Debug.h"

namespace
{
	XMVECTOR vFront = { 0,0,1,0 };
	float moveSpeed = 0.1f;
}
//コンストラクタ
Tank::Tank(GameObject* parent)
	: GameObject(parent, "Tank"), hModel_(-1)
{

}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("Tankbody.fbx");
}

void Tank::Update()
{
	if (Input::IsKeyDown(DIK_A))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKeyDown(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
	}
	if (Input::IsKeyDown(DIK_W))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		//XMVector3TransformCoordは、ベクトルを行列で変換する関数。回転行列をベクトル荷掛けると回転ベクトルが得られる。
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
		vPos = vPos + moveSpeed * vMove;

		vPos = vPos + moveSpeed * vFront;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	Debug::Log("Y Angle=");
	Debug::Log(transform_.rotate_.y, true);
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
