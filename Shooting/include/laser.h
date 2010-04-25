/*��{�I�֐��R��*/
void shotLaser();
int addLaser(int index,int targetType,void* target);
void moveLaser();
void drawLaser();
/*�^�[�Q�b�g�̎��*/
#define LASER_TARGET_BOSS	1
#define LASER_TARGET_FOE 	2

/*���[�U�̍ő�{��*/
#define LASER_MAX			GAUGE_NUM
/*��{�̃��[�U�ɂ��E�E�E*/
#define LASER_UNIT_MAX		12

/*���[�U��{������̃_���[�W*/
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
	int radLimit;			//�p�x����
	Boss *targetb;
	Foe *targetf;
	Point *targetPt;
	LaserUnit unit[LASER_UNIT_MAX];
	int count;
}Laser;
Laser laser[LASER_MAX];
