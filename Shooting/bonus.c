#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>
#include <PGL.h>

#include "include/main.h"
#include "include/move.h"
#include "include/ship.h"
#include "include/bullet.h"
#include "include/bonus.h"
#include "include/foe.h"

/*ボーナスの準備*/
Bonus* addBonus(){
	int i=0;
	for(;i<BONUS_MAX;i++){
		if(bonus[i].state == NOT_EXIST){
			bonus[i].state = EXIST;
			return &bonus[i];
		}
	}
	return NULL;
}

/*弾からボーナスへ変換する　ただし，座標とスピードだけ^^;*/
void translateBulletToBonus(Bonus* bonus,const Bullet* bul){
	bonus->pt.x = bul->pt.x;
	bonus->pt.y = bul->pt.y;
	bonus->spd.x = bul->spd.x;
	bonus->spd.y = bul->spd.y;
}
/*描写関連*/
void moveBonus(){
	int i=0;
	for(;i<BONUS_MAX;i++){
		if(bonus[i].state == EXIST){
			Bonus* bns = &bonus[i];
			/*画面との当たり判定*/
			if(!isInGameSpace(&bns->pt,20)){
				bns->state = NOT_EXIST;
				continue;
			}
			uint distance = 0;
			/*力が及ぶか？*/
			if(Ship.isTouching) bns->isTouched = TRUE;
			if(bns->isTouched){
				distance = moveByForce(&bns->spd,&bns->pt,bns->weight);
			}else{
				/*通常の動き*/
				bns->pt.x += bns->spd.x;
				bns->pt.y += bns->spd.y;
				/*距離は求める*/
				uint x = Ship.pt.x - bns->pt.x;
				uint y = Ship.pt.y - bns->pt.y;
				distance = sqrti(getDistance2(x,y)) << BIT;
			}
			/*当たり判定*/
			if(distance <= (bns->pt.radius + Ship.pt.radius)){
				Ship_getBonus();
				bns->state = NOT_EXIST;
			}
		}
	}
}
void drawBonus(){
	glPoint pt;
	int i=0;
	for(;i<BONUS_MAX;i++){
		if(bonus[i].state == EXIST){
			getPaintedPoint(&pt,&bonus[i].pt);
			glColor3f(1.0 , 0.4 , 0.4);
			glPointSize(pt.radius*2);
			glBegin(GL_POINTS);
				glVertex2f(pt.x , pt.y);
			glEnd();
		}
	}
}
