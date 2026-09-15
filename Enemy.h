#pragma once
#include "Engine/GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* pTarget) override;

	void SetPosition(const XMFLOAT3& pos) { transform_.position_ = pos; }

private:
	int hModel_; 
};