/*�B��̑��݂Ȃ̂�Typedef���͗p���܂���*/
struct{
	int kind;					//[���g�p]���@�̎��
	Point pt;					//���W
	Vector spd;					//�X�s�[�h
	int shield;					//�V�[���h
	int shieldMax;				//�V�[���h�ő�l
	int damage;					//�̓�����_���[�W
	uint power;					//�����t����͂̃p���[
	int gauge;					//�Q�[�W
	int isBombShooting;			//�{�����������Ă��邩�A�ۂ��B
	int isShotKeyPressed;		//�e�������Ă��邩�ۂ�
	int isPrevShotKeyPressed;	//�O�̃t���[���͂ǂ���������
	int isTouching;				//����̃t���[������V���b�g�{�^���������n�߂��ꍇ��true
	int shotLimit;				//�V���b�g�������~�b�g
}Ship;

unsigned long Score;			//�X�R�A�B

#define SHIP_POWER_MAX 512	//�����t����͂̍ő�l
#define SHOT_LIMIT 3		//���t���[���Ɉ�񂵂����ĂȂ��̂�

#define GAUGE_UNIT	10						//�Q�[�W������߂�̂ɕK�v�ȃ{�[�i�X��
#define GAUGE_NUM	12						//�Q�[�W�̖{��
#define GAUGE_MAX	(GAUGE_UNIT*GAUGE_NUM)	//�Q�[�W�ő�l

#define SHIP_MAX_BONUS 100	//�{�[�i�X�̍ő�l

void initShip();
void moveShip();
void drawShip();
void Ship_addDamage(int damage);
void Ship_getBonus();
void Ship_addScore(unsigned int score);

glPoint ShipPaintedPoint;	//�`�悳���|�C���g
