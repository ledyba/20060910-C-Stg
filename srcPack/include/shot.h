/*����*/
void initShot();
/*�`�ʊ֘A*/
void moveShot();
void drawShot();
/*�\����*/
#define SHOT_MAX 64
typedef struct{
	int kind;		//�e�̎��
	Point pt;		//���W
	Vector spd;		//�X�s�[�h
	uint state;		//���
	int damage;		//�_���[�W
}Shot;
Shot shot[SHOT_MAX];
/*�e�̏���*/
Shot* addShot();
