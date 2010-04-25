#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/gfx/sprite.h"
#include "include/screen.h"
//#include "include/move.h"
#include "include/ship.h"
#include "include/foe.h"
#include "include/boss.h"
#include "include/laser.h"

void shotLaser(){
	int i,left=0;
	/*���Ă郌�[�U�����m�F*/
	for(i=0;i<LASER_MAX;i++)  if(laser[i].unit[LASER_UNIT_MAX-1].state == NOT_EXIST)left++;
	left = min(left,Ship.gauge/GAUGE_UNIT);
	if(left <= 0)	return;
	/*�^�[�Q�b�g�I���B*/
	int locked,leftShield;
	i=0;//�C���f�b�N�X�̃��Z�b�g
	/*�{�X*/
	if(boss.state == EXIST){
		leftShield = (boss.shield - boss.laserLockedOn * LASER_DAMAGE);
		if(leftShield > 0){
			locked = max(1,min(left, (leftShield/ LASER_DAMAGE)+1));
			left -= locked;
			for(;i<LASER_MAX && locked > 0;i++,locked--){
				if(addLaser(i,LASER_TARGET_BOSS,(void*)&boss))	{
					Ship.gauge -= GAUGE_UNIT;
				}
			}
			/*�{����0�Ȃ�Δ�����*/
			if(left <= 0)	return;
		}
	}
	/*���܂��Ă���̂ŎG���ɂ܂킷*/
	int foeNum;
	Foe* target;
	for(foeNum = 0;foeNum<LASER_MAX;foeNum++){
		target = getNearistFoe(foeNum);
		if(!target)	return;		//�G�����[�U�̖{�������������甲����
		/*i�͏��������Ȃ��̂��~�\�B*/
		leftShield = (target->shield - target->laserLockedOn * LASER_DAMAGE);
		if(leftShield > 0){
			locked = max(1,min(left,(leftShield / LASER_DAMAGE)+1));
			left -= locked;
			for(;i<LASER_MAX && locked > 0;i++,locked--){
				if(addLaser(i,LASER_TARGET_FOE,(void*)target))	{
					Ship.gauge -= GAUGE_UNIT;
				}
			}
			/*�{����0�Ȃ�Δ�����*/
			if(left <= 0)	return;
		}
	}
}
#define LASER_SPEED (10<<BIT)
static int LaserDefaultCount[6]={0,1,3,5,6,8};
int addLaser(int index,int targetType,void* target){
	if(laser[index].unit[LASER_UNIT_MAX-1].state == NOT_EXIST && target != NULL){
		Laser *lsr = &laser[index];
		/*�^�[�Q�b�g�^�C�v�ʐݒ�*/
		lsr->targetType = targetType;
		switch(targetType){
			case LASER_TARGET_BOSS:
				lsr->targetb = (Boss*)target;
				lsr->targetPt = &lsr->targetb->pt;
				lsr->targetb->laserLockedOn++;
				break;
			case LASER_TARGET_FOE:
				lsr->targetf = (Foe*)target;
				lsr->targetPt = &lsr->targetf->pt;
				lsr->targetf->laserLockedOn++;
				break;
		}
		/*�p�x�����ݒ�*/
		lsr->count = LaserDefaultCount[index>>1];
		lsr->radLimit = 10;
		/*�^�[�Q�b�g�͐����Ă���H*/
		lsr->isTargetAlive = TRUE;
		/*�ŏ��̌����̐ݒ�*/
		Vector vec;
		/*�ŏ��͌����������Ĕ��˂��܂��B�[�����[�U�����̋N����`���܂��B*/
		vec.x = 0;
		vec.y = LASER_SPEED;
		vec.speed = LASER_SPEED;
		uint theta;
			if(index & 1){	/*���*/
				theta = index*(-10);
			}else{			/*������*/
				theta = (index+1)*10;
			}
		rotateVector(&vec,theta);//�������ɃA���Ȃ̂ł�����Ɖ�]�����܂��B
		/*���j�b�g�X�̐ݒ�*/
		int i;
		LaserUnit *unit = NULL;
		for(i=0;i<LASER_UNIT_MAX;i++){
			unit = &lsr->unit[i];
			/*�ꏊ�ɂ��Ă͂���������Ƃ������悭�E�E�E�B*/
			unit->state = EXIST;
			unit->pt.x = Ship.pt.x;
			unit->pt.y = Ship.pt.y;
			unit->pt.height = 5<<BIT;
			unit->pt.width = 5<<BIT;

			unit->pt.showHeight = 10<<BIT;
			unit->pt.showWidth = 5<<BIT;

			unit->pt.radius = 5<<BIT;
			unit->spd = vec;
		}
		return TRUE;
	}
	return FALSE;
}

void moveLaser(){
	int i,j;
	for(i=0;i<LASER_MAX;i++){
		if(laser[i].unit[LASER_UNIT_MAX-1].state == EXIST){
			Laser* lsr = &laser[i];
			/*�^�[�Q�b�g�������Ă��邩�ǂ����̌���*/
			if(lsr->isTargetAlive){
				switch(lsr->targetType){
					case LASER_TARGET_BOSS:
						lsr->isTargetAlive &= (lsr->targetb->state == EXIST);
						break;
					case LASER_TARGET_FOE:
						lsr->isTargetAlive &= (lsr->targetf->state == EXIST);
						break;
				}
			}
			/*���[�U�𓮂���*/
			for(j=0;j<LASER_UNIT_MAX;j++){
				/*�w���̂���ςȂ̂ŁA�|�C���^�Ɉ����[����B*/
				LaserUnit *unit = &lsr->unit[j];
				/*�V���̌��*/
				unit->oldPt  = unit->pt;
				unit->oldSpd = unit->spd;
				unit->oldState = unit->state;
				if(unit->state == EXIST){
					if(j == 0){
						if(lsr->count>14){
							/*���[�U�̐擪�̏���*/
							if(lsr->isTargetAlive){	/*�^�[�Q�b�g���܂������Ă���*/
								/*�z�[�~���O����*/
								Vector foeVec,rightVec,leftVec;
								/*�G�ւ̑��x�x�N�g�����擾*/
								getVector(&foeVec,&unit->pt,lsr->targetPt,LASER_SPEED);
								/*�E���̊p�x����*/
								rightVec = unit->spd;
								rotateVector(&rightVec,lsr->radLimit);
								if(unit->spd.x * foeVec.x + unit->spd.y * foeVec.y 
								>= unit->spd.x * rightVec.x + unit->spd.y * rightVec.y){/*�p�x�����`�F�b�N*/
									/*�͈͓�*/
									unit->spd = foeVec;
								}else{
									/*�͈͊O*/
									/*�����̊p�x����*/
									leftVec = unit->spd;
									rotateVector(&leftVec,-lsr->radLimit);
									if(foeVec.x * rightVec.x + foeVec.y * rightVec.y
									>= foeVec.x * leftVec.y + foeVec.y * leftVec.y){
										unit->spd = rightVec;
									}else{
										unit->spd = leftVec;
									}
								}
								/*���肪����̂́A��[�̈�ӏ������I*/
								if(isHitSquare(lsr->targetPt,&unit->pt,0)){
									unit->state = NOT_EXIST;
									/*�_���[�W��^����*/
									switch(lsr->targetType){
										case LASER_TARGET_BOSS:
											damageBoss(LASER_DAMAGE);
											lsr->targetb->laserLockedOn--;
											break;
										case LASER_TARGET_FOE:
											damageFoe(lsr->targetf,LASER_DAMAGE);
											lsr->targetf->laserLockedOn--;
											break;
									}
								}
							}

						}else{
							//�ŏ��͂܂���ɔ�΂��B�����d�l�B
							if((i & 1) != 0)	rotateVector(&unit->spd,-lsr->radLimit);
							else				rotateVector(&unit->spd, lsr->radLimit);
						}

						/*�ړ�*/
						unit->pt.x  += unit->spd.x;
						unit->pt.y  += unit->spd.y;

						/*��ʓ��ɑ��݂��邩�A�ۂ��B*/
						if(!isInGameSpace(&unit->pt,100)) unit->state = NOT_EXIST;
					}else{
						/*�擪�łȂ��Ȃ�΁A��O��ǂ�������B*/
						unit->pt  = lsr->unit[j-1].oldPt;
						unit->spd = lsr->unit[j-1].oldSpd;
						unit->state = lsr->unit[j-1].oldState;
					}
				}
			}
			/*�J�E���g*/
			lsr->count++;
			/*�p�x�������͂���*/
			if(lsr->radLimit < 360 && !(lsr->count & 7) && lsr->count > 30)lsr->radLimit++;
		}
	}
}
void drawLaser(){
	glPoint pt;
	int i,j;
	/*���Z����*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for(i=0;i<LASER_MAX;i++){
		/*���ꂼ��̏ꏊ�̕`��*/
		for(j=LASER_UNIT_MAX-1;j>=0;j--){
			if(laser[i].unit[j].state == EXIST){
				float tmp = ((float)j)/LASER_UNIT_MAX;
				glColor4f(1.0f , tmp , 1.0f , (1.0f-tmp)*0.7);
				getPaintedPoint(&pt,&laser[i].unit[j].pt);
				glPushMatrix();
				glTranslatef(pt.x, pt.y, 0);
				glRotatef(getTheta(&laser[i].unit[j].spd), 0, 0, 1);
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
		glDisable(GL_BLEND);

}
