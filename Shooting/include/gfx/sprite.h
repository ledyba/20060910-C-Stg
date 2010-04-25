/*�e�N�X�`�����Ǘ�����A�X�v���C�g*/

typedef struct{
	GLuint TexID;		//�e�N�X�`��ID
	int	Width;		//�h�b�g��
	int RealWidth;
	int	Height;		//�h�b�g��
	int RealHeight;
	GLfloat WidthF;		//���̊���
	GLfloat HeightF;	//�c�̊���
}SPRITE;

void getSprite(SPRITE* sprite,SDL_Surface* Image);
void deleteSprite(SPRITE* sprite);
void drawSprite(const SPRITE* sprite,const glPoint* point,int x,int y, int w, int h, float angle);
/*��ׂ̂���ōł��������̂�T��*/
int getMinPowerOfTwo(int num);
void getSpriteFromOPS(SPRITE *sprite,SDL_RWops* data);
