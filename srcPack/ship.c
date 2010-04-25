#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/gfx/sprite.h"
#include "include/screen.h"

#include "include/input.h"
#include "include/ship.h"
#include "include/shot.h"

#include "include/foe.h"
#include "include/boss.h"
#include "include/laser.h"

void initShip(){
	/*���@�𕪂���̂͂����ŁE�E�E*/

	/*���W�ݒ�*/
	Ship.pt.radius = 2 << BIT;
	Ship.pt.x = (GAME_SCREEN_WIDTH >> 1) << BIT;
	Ship.pt.y = (GAME_SCREEN_HEIGHT-(GAME_SCREEN_HEIGHT >> 2)) << BIT;
	Ship.pt.height = 2 << BIT;
	Ship.pt.width = 2 << BIT;
	/*�X�s�[�h�ݒ�*/
	Ship.spd.x = 3 << BIT;
	Ship.spd.y = 3 << BIT;
	/*�c�@�ݒ�C���̑�*/
	Ship.shield = 100;
	Ship.shieldMax = 100;
	Ship.power = 0;
	Ship.gauge = 120;
	Score = 0x0;
}


void moveShip(){
	uint spdX = Ship.spd.x;
	uint spdY = Ship.spd.y;
	/*�L�[���͂Ŏ��@�̈ړ�*/
	if((Input & PAD_UP) != 0 && (Ship.pt.y > ((GAME_SCREEN_HEIGHT << BIT)>>4)))
		Ship.pt.y -= spdY;
	if((Input & PAD_DOWN) != 0 && (Ship.pt.y < ((GAME_SCREEN_HEIGHT<<BIT) - (GAME_SCREEN_HEIGHT <<BIT>> 4))) )
		Ship.pt.y += spdY;
	if((Input & PAD_LEFT) != 0 && (Ship.pt.x > (GAME_SCREEN_WIDTH << BIT)>>4))
		Ship.pt.x -= spdX;
	if((Input & PAD_RIGHT) != 0 && (Ship.pt.x < (GAME_SCREEN_WIDTH << BIT)-(GAME_SCREEN_WIDTH<<BIT>>4)))
		Ship.pt.x += spdX;
	/*�O�����Ă������ǂ����̕ۑ�*/
	Ship.isPrevShotKeyPressed = Ship.isShotKeyPressed;
	if(Input & PadShotKey){
		Ship.isShotKeyPressed = TRUE;
	}else{
		Ship.isShotKeyPressed = FALSE;
	}
	if(Ship.isShotKeyPressed){
		if(!Ship.isPrevShotKeyPressed){
			/*�O��͉����ĂȂ� = ���񂩂牟���n�߂��ꍇ*/
			Ship.isTouching = TRUE;
			if(Ship.power < SHIP_POWER_MAX-20)Ship.power+=20;
			else Ship.power = SHIP_POWER_MAX;
		}else{
			/*�����ł͂Ȃ��ꍇ*/
			Ship.isTouching = FALSE;
		}
		/*�V���b�g�{�^���������Ă�ƃp���[��������*/
		if(Ship.power < SHIP_POWER_MAX)Ship.power++;
		if(Ship.shotLimit <= 0){
			/*���~�b�g��0�Ȃ�e������*/
			Shot *sh = addShot();
			if(sh != NULL){
				sh->pt.x = Ship.pt.x;
				sh->pt.y = Ship.pt.y;
				sh->pt.width  = 4  << BIT;
				sh->pt.height = 10 << BIT;
				sh->pt.showWidth  = 4  << BIT;
				sh->pt.showHeight = 10 << BIT;
				sh->spd.x = 0;
				sh->spd.y = -20 << BIT;
				sh->damage = 1;
			}
			sh = addShot();
			if(sh != NULL){
				sh->pt.x = Ship.pt.x;
				sh->pt.y = Ship.pt.y;
				sh->pt.width  = 4  << BIT;
				sh->pt.height = 10 << BIT;
				sh->pt.showWidth  = 4  << BIT;
				sh->pt.showHeight = 10 << BIT;
				sh->spd.x = -3<<BIT;
				sh->spd.y = -20 << BIT;
				sh->damage = 1;
			}
			sh = addShot();
			if(sh != NULL){
				sh->pt.x = Ship.pt.x;
				sh->pt.y = Ship.pt.y;
				sh->pt.width  = 4  << BIT;
				sh->pt.height = 10 << BIT;
				sh->pt.showWidth  = 4  << BIT;
				sh->pt.showHeight = 10 << BIT;
				sh->spd.x = 3<<BIT;
				sh->spd.y = -20 << BIT;
				sh->damage = 1;
			}
			Ship.shotLimit += SHOT_LIMIT;
		}else{
			/*�e�����ĂȂ��ꍇ�̓��~�b�g������*/
			Ship.shotLimit--;
		}
	}else{
		/*�����ĂȂ��Ƌt�Ɍ���*/
		if(Ship.power >= 1){
			Ship.power--;
		}else if(Ship.power <= -1){
			Ship.power++;
		}
	}
	Ship.isBombShooting = FALSE;
	if(((Input & PadBombKey) && ((PrevInput & PadBombKey) == 0))){/*����{�^�����������i�A�ŕK�{�j*/
		if(Ship.isShotKeyPressed){			/*�����Ă���Œ��Ȃ�΁A�͂̌y��*/
	/*����{�^���������ƃp���[��0�ɂȂ�*/
			if(Ship.gauge-GAUGE_UNIT >= 0){				/*�Q�[�W�����Ă��Ԃł���B*/
				Ship.gauge-=GAUGE_UNIT;//�Q�[�W������
				if(Ship.power >= 256){					/*������x�傫���ƁC0�ɂ܂ň�C�ɖ߂�*/
					Ship.isBombShooting = TRUE;
					Ship.power = 0;
				}else if(Ship.power >= -(SHIP_POWER_MAX)){		/*����ȊO�͕��ʂɌ��炷*/
					Ship.isBombShooting = TRUE;
					Ship.power -= 256;
					if(Ship.power < -(SHIP_POWER_MAX))Ship.power = -(SHIP_POWER_MAX);
				}
			}
		}else{
			/*�z�[�~���O���[�U*/
			shotLaser();
		}
	}
}
void drawShip(){
	glColor3f(0.0 , 0.0 , 1.0);
	getPaintedPoint(&ShipPaintedPoint,&Ship.pt);
	glPointSize(ShipPaintedPoint.radius * 2);
	glBegin(GL_POINTS);
		glVertex2f(ShipPaintedPoint.x , ShipPaintedPoint.y);
	glEnd();
}
/*�_���[�W��^����*/
void Ship_addDamage(int damage){
	if(Ship.shield > 0)
	Ship.shield -= damage;
}
unsigned long lastBonusTime;	//�Ō�ɂ��{�[�i�X���擾�������H
/*�{�[�i�X�_���[�W�̎擾*/
void Ship_getBonus(){
	/*���̎擾*/
	unsigned long diff = FrameCount - lastBonusTime;
	if(diff == 0)diff = 1;
	/*�X�V*/
	lastBonusTime = FrameCount;
	/*�X�R�A����*/
	Score += SHIP_MAX_BONUS / diff;
	/*�z�[�~���O���[�U����*/
	if(Ship.gauge < GAUGE_MAX) Ship.gauge++;
}
void Ship_addScore(unsigned int score){
	Score += score;
}
