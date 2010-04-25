/*唯一の存在なのでTypedef等は用いません*/
struct{
	int kind;					//[未使用]自機の種類
	Point pt;					//座標
	Vector spd;					//スピード
	int shield;					//シールド
	int shieldMax;				//シールド最大値
	int damage;					//体当たりダメージ
	uint power;					//引っ付ける力のパワー
	int gauge;					//ゲージ
	int isBombShooting;			//ボムを今撃っているか、否か。
	int isShotKeyPressed;		//弾を撃っているか否か
	int isPrevShotKeyPressed;	//前のフレームはどうだったか
	int isTouching;				//今回のフレームからショットボタンを押し始めた場合にtrue
	int shotLimit;				//ショットを撃つリミット
}Ship;

unsigned long Score;			//スコア。

#define SHIP_POWER_MAX 512	//引き付ける力の最大値
#define SHOT_LIMIT 3		//何フレームに一回しか撃てないのか

#define GAUGE_UNIT	10						//ゲージを一つ溜めるのに必要なボーナス数
#define GAUGE_NUM	12						//ゲージの本数
#define GAUGE_MAX	(GAUGE_UNIT*GAUGE_NUM)	//ゲージ最大値

#define SHIP_MAX_BONUS 100	//ボーナスの最大値

void initShip();
void moveShip();
void drawShip();
void Ship_addDamage(int damage);
void Ship_getBonus();
void Ship_addScore(unsigned int score);

glPoint ShipPaintedPoint;	//描画されるポイント
