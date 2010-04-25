/*スプライトの一部分を表すオブジェクト*/

typedef struct{
	SPRITE* sprite;
	int x,y,width,height;
}SPRITE_AREA;

void makeSpriteArea(SPRITE_AREA* sprite_area,SPRITE* sprite,int x,int y,int w,int h);
void drawSpriteArea(const glPoint* point,const SPRITE_AREA* sprite_area,float angle);
