#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Bullet : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);
	~Bullet(){}
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetMoveVector(XMFLOAT3 move) { move_ = move; }
private:
	int hModel_;//タンクヘッドモデル
	XMFLOAT3 move_;
};
