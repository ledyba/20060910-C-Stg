#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/shot.h"
#include "include/bullet.h"
#include "include/bonus.h"
#include "include/foe.h"
#include "include/boss.h"

/*準備します*/
void initShot(){
}

/*弾を追加します*/
Shot* addShot(){
	int i=0;
	for(;i<SHOT_MAX;i++){
		if(shot[i].state == NOT_EXIST){
			shot[i].state = EXIST;
			return &shot[i];
		}
	}
	return NULL;
}


/*弾を移動させます*/
void moveShot(){
	int i=0;
	for(;i<SHOT_MAX;i++){
		if(shot[i].state == EXIST){
			Shot *sht = &shot[i];
			/*画面との当たり判定*/
			if(!isInGameSpace(&sht->pt,10)){
				sht->state = NOT_EXIST;
				continue;
			}
			/*移動*/
			sht->pt.x += sht->spd.x;
			sht->pt.y += sht->spd.y;
			/*当たり判定*/
			int j=0;
			for(;j<FOE_MAX;j++){
				if(foe[j].state == EXIST){
					if(isHitSquare(&sht->pt,&foe[j].pt,0)){
						sht->state = NOT_EXIST;
						damageFoe(&foe[j],sht->damage);
					}
				}
			}
			/*ボス*/
			if(boss.state == EXIST && isHitSquare(&sht->pt,&boss.pt,0)){
				damageBoss(sht->damage);
				sht->state = NOT_EXIST;
			}
		}
	}
}

void drawShot(){
	glPoint pt;
	int i=0;
	for(;i<SHOT_MAX;i++){
		if(shot[i].state == EXIST){
			Shot *sh = &shot[i];
			getPaintedPoint(&pt,&sh->pt);
			glPushMatrix();
			glTranslatef(pt.x, pt.y, 0);
//			glRotatef(90.0f-getTheta(&sh->spd), 0, 0, 1);
//			fprintf(stdout,"%f",getTheta(&sh->spd));
			glColor3f(0.0 , 1.0 , 1.0);
		glBegin(GL_QUADS);
			glVertex2d(-pt.width, -pt.height);
	  		glVertex2d(pt.width,-pt.height);
	  		glVertex2d(pt.width,pt.height);
			glVertex2d(-pt.width,pt.height);
		glEnd();
			glPopMatrix();
		}
	}
}
