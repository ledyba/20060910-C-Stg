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

/*�{�[�i�X�̏���*/
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

/*�e����{�[�i�X�֕ϊ�����@�������C���W�ƃX�s�[�h����^^;*/
void translateBulletToBonus(Bonus* bonus,const Bullet* bul){
	bonus->pt.x = bul->pt.x;
	bonus->pt.y = bul->pt.y;
	bonus->spd.x = bul->spd.x;
	bonus->spd.y = bul->spd.y;
}
/*�`�ʊ֘A*/
void moveBonus(){
	int i=0;
	for(;i<BONUS_MAX;i++){
		if(bonus[i].state == EXIST){
			Bonus* bns = &bonus[i];
			/*��ʂƂ̓����蔻��*/
			if(!isInGameSpace(&bns->pt,20)){
				bns->state = NOT_EXIST;
				continue;
			}
			uint distance = 0;
			/*�͂��y�Ԃ��H*/
			if(Ship.isTouching) bns->isTouched = TRUE;
			if(bns->isTouched){
				distance = moveByForce(&bns->spd,&bns->pt,bns->weight);
			}else{
				/*�ʏ�̓���*/
				bns->pt.x += bns->spd.x;
				bns->pt.y += bns->spd.y;
				/*�����͋��߂�*/
				uint x = Ship.pt.x - bns->pt.x;
				uint y = Ship.pt.y - bns->pt.y;
				distance = sqrti(getDistance2(x,y)) << BIT;
			}
			/*�����蔻��*/
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
