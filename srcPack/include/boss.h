typedef struct{
	int state;
	Point pt;
	int shield;			//シールド
	int laserLockedOn;	//レーザにロックオンされている本数
	int limit;
}Boss;

Boss boss;
Boss* addBoss();
void damageBoss(int damage);
void moveBoss();
void drawBoss();
