/*�ő�̒e��*/
#define BULLET_MAX 1024

typedef struct{
	int kind;		//�e�̎��
	Point pt;		//���W
	Vector spd;		//�X�s�[�h
	uint weight;	//�d��
	uint state;		//���
	int damage;		//�_���[�W
	int isTouched;	//�͂��y��ł��邩
	int limit;		//������܂ł̃��~�b�g
}Bullet;

/*�e�̔z��m��*/
Bullet bullet[BULLET_MAX];

/*�e��ǉ����܂�*/
Bullet* addBullet();
/*�e���ړ������܂�*/
void moveBullet();
void drawBullet();
