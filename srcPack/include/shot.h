/*準備*/
void initShot();
/*描写関連*/
void moveShot();
void drawShot();
/*構造体*/
#define SHOT_MAX 64
typedef struct{
	int kind;		//弾の種類
	Point pt;		//座標
	Vector spd;		//スピード
	uint state;		//状態
	int damage;		//ダメージ
}Shot;
Shot shot[SHOT_MAX];
/*弾の準備*/
Shot* addShot();
