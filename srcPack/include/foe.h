/*準備*/
void initFoe();
/*描写関連*/
void moveFoe();
void drawFoe();
/*構造体*/
#define FOE_MAX 128
typedef struct{
	int kind;			//敵の種類
	Point pt;			//座標
	Vector spd;			//スピード
	uint weight;		//重さ
	uint state;			//状態
	int damage;			//ダメージ
	int shield;			//シールド
	int laserLockedOn;	//レーザにロックオンされている本数
	int isTouched;		//力が及んでいるか
	int limit;			//消えるまでのカウント
}Foe;
Foe foe[FOE_MAX];
/*敵の準備*/
Foe* addFoe();
/*ダメージ*/
void damageFoe(Foe* foe,int damage);

/*ランキングリセット*/
void resetRanking();
/*並び替え*/
void sortFoe(Foe* foe, uint dis);
/*近いFoeのリストを取得*/
Foe* getNearistFoe(int num);
