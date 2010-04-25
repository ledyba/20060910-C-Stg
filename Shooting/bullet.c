#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/move.h"
#include "include/ship.h"
#include "include/bullet.h"
#include "include/foe.h"

/*�e��ǉ����܂�*/
Bullet* addBullet(){
	/*�V���b�g�������Ă�Ԃ͒e���o�Ȃ�*/
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


/*�e���ړ������܂�*/
void moveBullet(){
	int i=0;
	for(;i<BULLET_MAX;i++){
		if(bullet[i].state == EXIST){
			Bullet* bul = &bullet[i];
			/*��ʂƂ̓����蔻��@���~�b�g*/
			if(!isInGameSpace(&bul->pt,0) || bul->limit <= 0){
				bul->state = NOT_EXIST;
				continue;
			}
			/*�͂��y�Ԃ��H*/
			if(Ship.isTouching) bul->isTouched = TRUE;
			uint dis;
			if(bul->isTouched){
				/*�͂̋y��ł���΁C�͂̉e�����󂯂�*/
				dis = moveByForce(&bul->spd,&bul->pt,bul->weight);
			}else{
				/*�����łȂ���΁C�֐��|�C���^��p�������ʂ̏���*/
				/*��*/
				bul->pt.x += bul->spd.x;
				bul->pt.y += bul->spd.y;
				/*�����͋��߂�*/
				uint x = Ship.pt.x - bul->pt.x;
				uint y = Ship.pt.y - bul->pt.y;
				dis = sqrti(getDistance2(x,y)) << BIT;
			}
			/*�����蔻��*/
			if(dis < (bul->pt.radius + Ship.pt.radius)){
				/*�����菈��*/
				Ship_addDamage(bul->damage);
				bul->state = NOT_EXIST;
			}
			/*�^�C�����~�b�g�J�E���g*/
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


