#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/move.h"
#include "include/ship.h"
#include "include/bullet.h"
#include "include/foe.h"

/*弾を追加します*/
Bullet* addBullet(){
	/*ショットを押してる間は弾が出ない*/
	//if(Ship.isShotKeyPressed)return NULL;
	int i=0;
	for(;i<BULLET_MAX;i++){
		if(bullet[i].state == NOT_EXIST){
			bullet[i].state = EXIST;
			return &bullet[i];
		}
	}
	return NULL;
}


/*弾を移動させます*/
void moveBullet(){
	int i=0;
	for(;i<BULLET_MAX;i++){
		if(bullet[i].state == EXIST){
			Bullet* bul = &bullet[i];
			/*画面との当たり判定　リミット*/
			if(!isInGameSpace(&bul->pt,0) || bul->limit <= 0){
				bul->state = NOT_EXIST;
				continue;
			}
			/*力が及ぶか？*/
			if(Ship.isTouching) bul->isTouched = TRUE;
			uint dis;
			if(bul->isTouched){
				/*力の及んでいれば，力の影響を受ける*/
				dis = moveByForce(&bul->spd,&bul->pt,bul->weight);
			}else{
				/*そうでなければ，関数ポインタを用いた普通の処理*/
				/*仮*/
				bul->pt.x += bul->spd.x;
				bul->pt.y += bul->spd.y;
				/*距離は求める*/
				uint x = Ship.pt.x - bul->pt.x;
				uint y = Ship.pt.y - bul->pt.y;
				dis = sqrti(getDistance2(x,y)) << BIT;
			}
			/*当たり判定*/
			if(dis < (bul->pt.radius + Ship.pt.radius)){
				/*当たり処理*/
				Ship_addDamage(bul->damage);
				bul->state = NOT_EXIST;
			}
			/*タイムリミットカウント*/
			bul->limit--;
		}
	}
}

void drawBullet(){
	glPoint pt;
	int i=0;
	for(;i<BULLET_MAX;i++){
		if(bullet[i].state == EXIST){
			Bullet* bul = &bullet[i];
			getPaintedPoint(&pt,&bul->pt);
			if(bul->isTouched)	glColor3f(1.0 , 0.0 , 0.0);
			else				glColor3f(1.0 , 1.0 , 1.0);
			glPointSize(pt.radius*2);
			glBegin(GL_POINTS);
				glVertex2f(pt.x , pt.y);
			glEnd();
		}
	}
}


