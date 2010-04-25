/*基本的関数３つ*/
void shotLaser();
int addLaser(int index,int targetType,void* target);
void moveLaser();
void drawLaser();
/*ターゲットの種類*/
#define LASER_TARGET_BOSS	1
#define LASER_TARGET_FOE 	2

/*レーザの最大本数*/
#define LASER_MAX			GAUGE_NUM
/*一本のレーザにつき・・・*/
#define LASER_UNIT_MAX		12

/*レーザ一本あたりのダメージ*/
#define LASER_DAMAGE		10
typedef struct{
	int state;
	int oldState;
	Point pt;
	Vector spd;
	Point oldPt;
	Vector oldSpd;
}LaserUnit;
typedef struct{
	int isTargetAlive;
	int targetType;
	int radLimit;			//角度制限
	Boss *targetb;
	Foe *targetf;
	Point *targetPt;
	LaserUnit unit[LASER_UNIT_MAX];
	int count;
}Laser;
Laser laser[LASER_MAX];
