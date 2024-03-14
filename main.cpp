#include <Novice.h>
#include"Rendering/Player.h"
#include"Rendering/Camera.h"

const char kWindowTitle[] = "GC1A_01_イイヅカ_ソラ_title";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//カメラ
	Affine cameraCenter{ {1.0f,1.0f},0,{480,200} };//原点
	Speed cameraSpeed{ 1.0f / 50.0f,1.0f / 50.0f,5 };//拡縮や回転や移動のスピード
	Camera* camera = new Camera(cameraCenter,cameraSpeed);//インスタンス

	//プレイヤー
	Affine playerPosition{ {1.0f,1.0f},0,{0,0} };//原点からどれくらい離れているか
	Speed playerSpeed{ 1.0f / 50.0f,1.0f / 50.0f,10 };//拡縮や回転や移動のスピード
	Player* player = new Player(playerPosition,playerSpeed);//インスタス
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		camera->Update(keys);//カメラの更新
		player->Update(keys,camera);//プレイヤーの更新
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		camera->Draw();//カメラの描画
		player->Drawing(Novice::LoadTexture("white1x1.png"));//プレイヤーの描画
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	//削除
	delete player;
	delete camera;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
