#include "TankHead.h"
#include "Engine//Model.h"
#include"assert.h"
#include "Tank.h"
#include"Engine//Camera.h"

TankHead::TankHead(GameObject* parent)
	: GameObject(parent, "Tank"), hModel_(-1)
{

}

TankHead::~TankHead()
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
}

void TankHead::Update()
{
	Tank* tank= (Tank*)FindObject("Tank");
    transform_.position_;
	transform_.position_.y = transform_.position_.y + 5.0f;
	
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
