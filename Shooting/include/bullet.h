/*最大の弾数*/
#define BULLET_MAX 1024

typedef struct{
	int kind;		//弾の種類
	Point pt;		//座標
	Vector spd;		//スピード
	uint weight;	//重さ
	uint state;		//状態
	int damage;		//ダメージ
	int isTouched;	//力が及んでいるか
	int limit;		//消えるまでのリミット
}Bullet;

/*弾の配列確保*/
Bullet bullet[BULLET_MAX];

/*弾を追加します*/
Bullet* addBullet();
/*弾を移動させます*/
void moveBullet();
void drawBullet();
