/*テクスチャを管理する、スプライト*/

typedef struct{
	GLuint TexID;		//テクスチャID
	int	Width;		//ドット数
	int RealWidth;
	int	Height;		//ドット数
	int RealHeight;
	GLfloat WidthF;		//横の割合
	GLfloat HeightF;	//縦の割合
}SPRITE;

void getSprite(SPRITE* sprite,SDL_Surface* Image);
void deleteSprite(SPRITE* sprite);
void drawSprite(const SPRITE* sprite,const glPoint* point,int x,int y, int w, int h, float angle);
/*二のべき乗で最も小さいのを探す*/
int getMinPowerOfTwo(int num);
void getSpriteFromOPS(SPRITE *sprite,SDL_RWops* data);
