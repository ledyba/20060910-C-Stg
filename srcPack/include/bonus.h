/*�`�ʊ֘A*/
void moveBonus();
void drawBonus();
/*�\����*/
#define BONUS_MAX 1024
typedef struct{
	int kind;		//�{�[�i�X�̎��
	Point pt;		//���W
	Vector spd;		//�X�s�[�h
	uint weight;	//�d��
	uint state;		//���
	int isTouched;	//�͂��y�񂾂��A�ۂ��B
}Bonus;
Bonus bonus[BONUS_MAX];
/*�{�[�i�X�̏���*/
Bonus* addBonus();
/*�e����{�[�i�X�֕ϊ�����*/
void translateBulletToBonus(Bonus* bonus,const Bullet* foe);
