#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Tank : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Tank(GameObject* parent);
	~Tank();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void NowPosition();
private:
	int hModel_;//タンクモデル
	int camType_;//カメラの種類
	void SetFixedCam();

};
