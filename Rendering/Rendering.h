#pragma once
#include <assert.h>
#include <math.h>
#include "Struct.h"
#include <Novice.h>
class Rendering
{
public:
	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix3x3 Inverse(Matrix3x3 matrix);

	/// <summary>
	/// 掛け算
	/// </summary>
	/// <param name="matrix1"></param>
	/// <param name="matrix2"></param>
	/// <returns></returns>
	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

	/// <summary>
	/// トランスレートマトリックス
	/// </summary>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix3x3 MakeTranslateMatrix(Vector2 translate);

	/// <summary>
	/// ローテイトマトリックス
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	Matrix3x3 MakeRotateMatrix(float theta);

	/// <summary>
	/// スケールマトリックス
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix3x3 MakeScaleMatrix(Vector2 scale);

	/// <summary>
	/// SRTを変換する
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="vertex"></param>
	/// <returns></returns>
	Matrix3x3 MakeOrthographicMatrix(Point vertex);

	/// <summary>
	/// ビューポート変換
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

	/// <summary>
	/// アフィン行列
	/// </summary>
	/// <param name="affine"></param>
	/// <returns></returns>
	Matrix3x3 MakeAffineMatrix(Affine affine);

protected:

	/// <summary>
	/// ワールド行列の作成
	/// </summary>
	/// <param name="affine"></param>
	/// <returns></returns>
	Matrix3x3 MakeAffine(Affine affine);

	/// <summary>
	/// ビュー行列の作成
	/// </summary>
	/// <param name="cameraMatrix"></param>
	/// <returns></returns>
	Matrix3x3 ViewMatrix(Matrix3x3 cameraMatrix);

	/// <summary>
	/// 正射影行列の作成
	/// </summary>
	/// <param name="vertex"></param>
	/// <returns></returns>
	Matrix3x3 OrthoMatrix(Point vertex);

	/// <summary>
	/// ビュー行列の作成
	/// </summary>
	/// <param name="viewport"></param>
	/// <returns></returns>
	Matrix3x3 ViewportMatrix(LeftAndSize viewport);

	/// <summary>
	/// vpVp行列の作成
	/// </summary>
	/// <param name="viewMatrix"></param>
	/// <param name="orthoMatrix"></param>
	/// <param name="viewportMatrix"></param>
	/// <returns></returns>
	Matrix3x3 MakeVpVpMatrix(Matrix3x3 viewMatrix, Matrix3x3 orthoMatrix, Matrix3x3 viewportMatrix);

	/// <summary>
	/// カメラの座標変換
	/// </summary>
	/// <param name="local"></param>
	/// <param name="vpVpMatrix"></param>
	/// <returns></returns>
	LinePosition TransformLine(LinePosition local, Matrix3x3 vpVpMatrix);

	/// <summary>
	/// wvpVp行列の作成
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="screen"></param>
	Matrix3x3 WvpVpMatrix(Matrix3x3 worldMatrix, Matrix3x3 vpVpMatrix);

	/// <summary>
	/// 座標変換
	/// </summary>
	Vertex TransformSprite(Vertex local, Matrix3x3 wvpVpMatrix);

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void Draw(Vertex screen,int texture);
};

