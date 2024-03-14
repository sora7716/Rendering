#include "Rendering.h"

Matrix3x3 Rendering::Inverse(Matrix3x3 matrix) {

	Matrix3x3 result{};
	float cofactor = 1.0f / (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]
		);
	result.m[0][0] = cofactor * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = -(cofactor * (matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]));
	result.m[0][2] = cofactor * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	result.m[1][0] = -(cofactor * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));
	result.m[1][1] = cofactor * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = -(cofactor * (matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]));
	result.m[2][0] = cofactor * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = -(cofactor * (matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]));
	result.m[2][2] = cofactor * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return result;

}

Matrix3x3 Rendering::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 result = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;

}

Matrix3x3 Rendering::MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 result{
		1,0,0,
		0,1,0,
		translate.x,translate.y,1
	};
	return  result;
}

Matrix3x3 Rendering::MakeRotateMatrix(float theta) {
	Matrix3x3 result = { cosf(theta),sinf(theta),0,
		-sinf(theta),cosf(theta),0,
		0,0,1 };

	return result;
}

Matrix3x3 Rendering::MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 result{
		scale.x,0,0,
		0,scale.y,0,
		0,0,1,
	};
	return result;
}

Vector2 Rendering::Transform(Vector2 vector, Matrix3x3 matrix) {

	Vector2 result = {};
	result.x = { vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0] };
	result.y = { vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1] };
	float w  = vector.x *  matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	return result;

}

Matrix3x3 Rendering::MakeOrthographicMatrix(Point vertex) {

	Matrix3x3 result{
		2.0f / (vertex.right - vertex.left),0,0,
		0,2.0f / (vertex.top - vertex.bottom),0,
		(vertex.left + vertex.right) / (vertex.left - vertex.right),(vertex.top + vertex.bottom) / (vertex.bottom - vertex.top),1
	};
	return result;

}

Matrix3x3 Rendering::MakeViewportMatrix(float left, float top, float width, float height) {

	Matrix3x3 result{
		width / 2.0f,0,0,
		0,-height / 2.0f,0,
		left + width / 2.0f,top + height / 2.0f,1
	};
	return result;

}

Matrix3x3 Rendering::MakeAffineMatrix(Affine affine) {
	
	return Multiply(Multiply(MakeScaleMatrix(affine.scale), MakeRotateMatrix(affine.theta)), MakeTranslateMatrix(affine.translate));
}

Matrix3x3 Rendering::MakeAffine(Affine affine) {
	Matrix3x3 result=MakeAffineMatrix(affine);
	return result;
}

/// <summary>
/// ビューマトリックスの作成
/// </summary>
Matrix3x3 Rendering::ViewMatrix(Matrix3x3 cameraMatrix) {
	Matrix3x3 viewMatrix = Inverse(cameraMatrix);
	return viewMatrix;
}

/// <summary>
/// 正規化デバイスマトリックスの作成
/// </summary>
Matrix3x3 Rendering::OrthoMatrix(Point vertex) {
	Matrix3x3 orthoMatrix= MakeOrthographicMatrix(vertex);
	return orthoMatrix;
}

/// <summary>
/// ビューポートマトリックスの作成
/// </summary>
Matrix3x3 Rendering::ViewportMatrix(LeftAndSize viewport) {
	Matrix3x3 viewportMatrix_ = MakeViewportMatrix(viewport.left, viewport.top, viewport.width, viewport.height);
	return viewportMatrix_;
}

/// <summary>
/// vs = vpVp
/// </summary>
Matrix3x3 Rendering::MakeVpVpMatrix(Matrix3x3 viewMatrix,Matrix3x3 orthoMatrix,Matrix3x3 viewportMatrix) {
	/*ワールド座標系*/
	Matrix3x3 vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	/*ビュー座標系*/
	vpVpMatrix = Multiply(vpVpMatrix, viewportMatrix);

	return vpVpMatrix;
}
/// <summary>
/// カメラの座標変換
/// </summary>
LinePosition Rendering::TransformLine(LinePosition local,Matrix3x3 vpVpMatrix) {
	LinePosition screen{};
	screen.lateral.begin = Transform(local.lateral.begin, vpVpMatrix);
	screen.lateral.end   = Transform(local.lateral.end,   vpVpMatrix);
	screen.vert.begin    = Transform(local.vert.begin,    vpVpMatrix);
	screen.vert.end      = Transform(local.vert.end,      vpVpMatrix);

	return screen;
}

/// <summary>
/// wvpVp行列の作成
/// </summary>
/// <param name="worldMatrix"></param>
/// <param name="vpVpMatrix"></param>
/// <returns></returns>
Matrix3x3 Rendering::WvpVpMatrix(Matrix3x3 worldMatrix, Matrix3x3 vpVpMatrix) {
	return Multiply(worldMatrix, vpVpMatrix);
}

/// <summary>
/// 座標変換
/// </summary>
/// <param name="local"></param>
/// <param name="wvpVpMatrix"></param>
/// <returns></returns>
Vertex Rendering::TransformSprite(Vertex local, Matrix3x3 wvpVpMatrix) {
	Vertex result{};
	result.leftTop     = Rendering::Transform(local.leftTop,     wvpVpMatrix);
	result.leftBottom  = Rendering::Transform(local.leftBottom,  wvpVpMatrix);
	result.rightTop    = Rendering::Transform(local.rightTop,    wvpVpMatrix);
	result.rightBottom = Rendering::Transform(local.rightBottom, wvpVpMatrix);
	return result;
}

/// <summary>
/// オブジェクトの描画
/// </summary>
/// <param name="screen"></param>
/// <param name="texture"></param>
void Rendering::Draw(Vertex screen,int texture) {
	Novice::DrawQuad(
		(int)screen.leftTop.x,     (int)screen.leftTop.y,
		(int)screen.leftBottom.x,  (int)screen.leftBottom.y,
		(int)screen.rightTop.x,    (int)screen.rightTop.y,
		(int)screen.rightBottom.x, (int)screen.rightBottom.y,
		0, 0, 1, 1, texture, WHITE);
}