/*����*/
void initFoe();
/*�`�ʊ֘A*/
void moveFoe();
void drawFoe();
/*�\����*/
#define FOE_MAX 128
typedef struct{
	int kind;			//�G�̎��
	Point pt;			//���W
	Vector spd;			//�X�s�[�h
	uint weight;		//�d��
	uint state;			//���
	int damage;			//�_���[�W
	int shield;			//�V�[���h
	int laserLockedOn;	//���[�U�Ƀ��b�N�I������Ă���{��
	int isTouched;		//�͂��y��ł��邩
	int limit;			//������܂ł̃J�E���g
}Foe;
Foe foe[FOE_MAX];
/*�G�̏���*/
Foe* addFoe();
/*�_���[�W*/
void damageFoe(Foe* foe,int damage);

/*�����L���O���Z�b�g*/
void resetRanking();
/*���ёւ�*/
void sortFoe(Foe* foe, uint dis);
/*�߂�Foe�̃��X�g���擾*/
Foe* getNearistFoe(int num);
