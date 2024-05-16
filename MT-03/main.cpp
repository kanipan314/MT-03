#include <Novice.h>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "学籍番号";



struct Vector3
{
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

static const int kColumnwindth = 60;
static const int kRowwindth = 20;


void VectorScreenPrint(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnwindth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnwindth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnwindth * 3, y, "%s", label);
}

void MatrixScrennPrint(int x, int y, const Matrix4x4& matrix, const char* label) {

	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; row++) {
		for (int colum = 0; colum < 4; colum++) {
			Novice::ScreenPrintf(x + colum * kColumnwindth, y + (row + 1) * kRowwindth, "%6.02f", matrix.m[row][colum]);
		}
	}
}

Matrix4x4 MakeTranslateMatrix(Vector3 translate) {

	Matrix4x4 answer;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			answer.m[i][j] = 0;
			if (i == j) {
				answer.m[i][j] = 1;

			}
		}
	}
	
	answer.m[3][0] = translate.x;
	answer.m[3][1] = translate.y;
	answer.m[3][2] = translate.z;
	answer.m[3][3] = 1;

	return answer;
}

Matrix4x4 MekeScaleMatrix(Vector3 scale) {

	Matrix4x4 answer;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer.m[i][j] = 0;
		}
	}
	answer.m[0][0] = scale.x;
	answer.m[1][1] = scale.y;
	answer.m[2][2] = scale.z;
	answer.m[3][3] = 1;

	return answer;
}

Vector3 Transfom(Vector3 point, Matrix4x4 transform) {

	Vector3 answer;

	answer.x = point.x * transform.m[0][0] + point.y * transform.m[1][0] +
			   point.z * transform.m[2][0] + 1.0f * transform.m[3][0];
	answer.y = point.x * transform.m[0][1] + point.y * transform.m[1][1] +
			   point.z * transform.m[2][1] + 1.0f * transform.m[3][1];
	answer.z = point.x * transform.m[0][2] + point.y * transform.m[1][2] +
			   point.z * transform.m[2][2] + 1.0f * transform.m[3][2];

	float w = point.x * transform.m[0][3] + point.y * transform.m[1][3] +
			  point.z * transform.m[2][3] + 1.0f * transform.m[3][3];

	assert(w != 0.0f);

	answer.x /= w;
	answer.y /= w;
	answer.z /= w;

	return answer;

}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

		Vector3 translate{ 4.1f,2.6f,0.8f };
		Vector3 scale{ 1.5f,5.2f,7.3f };
		Vector3 point{ 2.3f,3.8f,1.4f };

		Matrix4x4 transformMatrix = {
			1.0f,2.0f,3.0f,4.0f,
			3.0f,1.0f,1.0f,2.0f,
			1.0f,4.0f,2.0f,3.0f,
			2.0f,2.0f,1.0f,3.0f
		};



		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = MekeScaleMatrix(scale);
		Vector3 transfomed = Transfom(point, transformMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrint(0, 0, transfomed, "transformed");
		MatrixScrennPrint(0, kRowwindth * 5, translateMatrix, "transleteMatrix");
		MatrixScrennPrint(0, kRowwindth * 10, scaleMatrix, "scaleMatrix");


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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
