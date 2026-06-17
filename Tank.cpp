#include "Tank.h"
#include "Engine//Model.h"
#include "Engine//Input.h"
#include  "Engine//Debug.h"
#include  "Ground.h"
#include  "Engine//Camera.h"
namespace
{
	XMVECTOR vFront = { 0,0,1,0 };
	const int CAM_TYPE_MAX = 3;
	float moveSpeed = 0.1f;//タンクのスピード
	const float CAM_HEIGHT_BIAS = 0.2f;//タンクの高さ
	enum CAM_TYPE
	{
		FIXED_CAM,//固定カメラ
		TPS_CAM,//三人称視点カメラ
		TPS_CAMROT,//三人称視点カメラ（回転）
		FPS_CAM,//一人称視点カメラ
	};
}
//コンストラクタ
Tank::Tank(GameObject* parent)
	: GameObject(parent, "Tank"), hModel_(-1),camType_(FIXED_CAM)
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
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//XMVector3TransformCoordは、ベクトルを行列で変換する関数。回転行列をベクトル荷掛けると回転ベクトルが得られる。
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + 5.0f;
		camPos.z = camPos.z - 13.0f;
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
		break;
	case TPS_CAMROT:
	{
		XMFLOAT3 camPos;
		XMVECTOR vCAM = { 0,3,-7,0 };
		vCAM = XMVector3TransformCoord(vCAM, matRot);
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
		break;
	case FPS_CAM:
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);
		Camera::SetTarget(camTarget);
		break;
	}

	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
	}

	Debug::Log("CAMTYPE=");
	Debug::Log(camType_, true);

	if (Input::IsKey(DIK_W))
	{
		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	//レイキャストして、浮いてたら地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は0より下に掘られて作られている。そうじゃないときはもっと上から！
	data.dir = { 0,-1,0 };//真下にレイを飛ばす
	
	Ground* pGround = (Ground*)FindObject("Ground");
	int hGroundModel = pGround->GetModelHandle();
	Model::RayCast(hGroundModel, &data);

	if (data.hit==true)
	{
		transform_.position_.y = - data.dist;
		//レイの発射一から、地面までの距離を引いて、地面をぴったりつける
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

void Tank::NowPosition()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//XMVector3TransformCoordは、ベクトルを行列で変換する関数。回転行列をベクトル荷掛けると回転ベクトルが得られる。
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
}

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}

void Tank::SetTpsCom()
{
	
}
