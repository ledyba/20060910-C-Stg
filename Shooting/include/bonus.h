/*描写関連*/
void moveBonus();
void drawBonus();
/*構造体*/
#define BONUS_MAX 1024
typedef struct{
	int kind;		//ボーナスの種類
	Point pt;		//座標
	Vector spd;		//スピード
	uint weight;	//重さ
	uint state;		//状態
	int isTouched;	//力が及んだか、否か。
}Bonus;
Bonus bonus[BONUS_MAX];
/*ボーナスの準備*/
Bonus* addBonus();
/*弾からボーナスへ変換する*/
void translateBulletToBonus(Bonus* bonus,const Bullet* foe);
