#include "Player.h"


/// <summary>
/// コンストラクター
/// </summary>
Player::Player(Affine affine,Speed speed) {
#pragma region 定義しないといけない
	//プレイヤーのローカル座標
	local_={
		{ -PLAYER_SIZE/2.0f   ,-PLAYER_SIZE / 2.0f },
		{ -PLAYER_SIZE / 2.0f ,PLAYER_SIZE / 2.0f  },
		{  PLAYER_SIZE / 2.0f ,-PLAYER_SIZE / 2.0f },
		{  PLAYER_SIZE / 2.0f ,PLAYER_SIZE / 2.0f  },
	};
	//プレイヤー 拡縮・回転・移動
	affine_ = affine;
	speed_ = speed;
#pragma endregion

	//スクリーン座標系に変化に使う
	screen_={};

	//ワールドマトリックス
	worldMatrix_ = {};
	//wvpVp
	wvpVpMatrix_ = {};
}

/// <summary>
/// 拡縮
/// </summary>
/// <param name="keys"></param>
void Player::Scale(char* keys) {
	if (keys[DIK_E] && keys[DIK_LSHIFT]) {
		if (affine_.scale.x > 0 || affine_.scale.y > 0) {
			affine_.scale.x -= speed_.scale;
			affine_.scale.y -= speed_.scale;
		}
	}
	if (keys[DIK_Q] && keys[DIK_LSHIFT]) {
		affine_.scale.x += speed_.scale;
		affine_.scale.y += speed_.scale;
	}
}

/// <summary>
/// 回転
/// </summary>
/// <param name="keys"></param>
void Player::Rotation(char* keys) {
	if (keys[DIK_C] && keys[DIK_LSHIFT]) {
		affine_.theta -= speed_.rotate;
	}				
	if (keys[DIK_Z] && keys[DIK_LSHIFT]) {
		affine_.theta += speed_.rotate;
	}
}

/// <summary>
/// 移動
/// </summary>
/// <param name="keys"></param>
void Player::Translate(char* keys) {
	if (keys[DIK_A])
	{
		affine_.translate.x -= speed_.translate;
	}
	if (keys[DIK_D])
	{
		affine_.translate.x += speed_.translate;
	}
	if (keys[DIK_W])
	{
		affine_.translate.y += speed_.translate;
	}
	if (keys[DIK_S])
	{
		affine_.translate.y -= speed_.translate;
	}
}

/// <summary>
/// 動き
/// </summary>
/// <param name="keys"></param>
void Player::Move(char *keys) {
	Scale(keys);
	Rotation(keys);
	Translate(keys);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="keys"></param>
/// <param name="camera"></param>
void Player::Update(char* keys,Camera*camera) {
	Move(keys);
	worldMatrix_=Rendering::MakeAffine(affine_);
	wvpVpMatrix_=Rendering::WvpVpMatrix(worldMatrix_,camera->GetVpVpMatrix());
	screen_ = Rendering::TransformSprite(local_, wvpVpMatrix_);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="texture"></param>
void Player::Drawing(int texture) {
	Draw(screen_,texture);
}
