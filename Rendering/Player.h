#pragma once
#include "Camera.h"
class Player:public Rendering
{
private:

#pragma region 定義しないといけない
	//プレイヤーのローカル座標
	Vertex local_;
	//プレイヤー 拡縮・回転・移動
	Affine affine_;

	//プレイヤーのスピード
	Speed speed_;
#pragma endregion

	//スクリーン座標系に変化に使う
	Vertex screen_;
	
	//ワールドマトリックス
	Matrix3x3 worldMatrix_;
	//wvpVp
	Matrix3x3 wvpVpMatrix_;

public:

	/// <summary>
	/// コンストラクター
	/// </summary>
	Player(Affine affine, Speed speed);

	/// <summary>
	/// 拡縮
	/// </summary>
	void Scale(char *keys);

	/// <summary>
	/// 回転
	/// </summary>
	/// <param name="keys"></param>
	void Rotation(char *keys);

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="keys"></param>
	void Translate(char *keys);

	/// <summary>
	/// プレイヤーのキー入力での動き
	/// </summary>
	/// <param name="keys"></param>
	void Move(char *keys);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="texture"></param>
	void Update(char* keys, Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="texture"></param>
	void Drawing(int texture);

};

