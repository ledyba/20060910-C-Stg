typedef struct{
	int state;
	Point pt;
	int shield;			//�V�[���h
	int laserLockedOn;	//���[�U�Ƀ��b�N�I������Ă���{��
	int limit;
}Boss;

Boss boss;
Boss* addBoss();
void damageBoss(int damage);
void moveBoss();
void drawBoss();
