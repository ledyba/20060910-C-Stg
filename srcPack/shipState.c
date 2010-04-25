#include <SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>

#include "include/main.h"
#include "include/input.h"
#include "include/music.h"
#include "include/point.h"
#include "include/gfx/sprite.h"
#include "include/screen.h"
#include "include/move.h"
#include "include/ship.h"
#include "include/shot.h"
#include "include/bullet.h"
#include "include/bonus.h"
#include "include/foe.h"
#include "include/shipState.h"

#include "include/stage/eventGenerator.h"

/*�X�R�A�E�̗͂Ȃǂ̕`�ʂ��s��*/

void initShipState(){
}
void drawShipState(){
	drawShipGauge();	//�Q�[�W�̕\��
}
/*�Q�[�W�ނ̕\��*/
void drawShipGauge(){
	/*�{�[�i�X*/
	drawShipBonusPowerGauge();
	/*�Ђ������*/
	drawShipAttractPowerGauge();
	/*������*/
	drawShipLifeGauge();
	/*�G�A�������̓{�X�̐����\��*/
	drawFoeOrBossLifeGauge();
	/*�X�R�A�\��*/
	drawScore();
}

/*�{�[�i�X�̃p���[�̕\��*/
void drawShipBonusPowerGauge(){
	int gauge = Ship.gauge;
	int i=0;
	ufloat x,y;
		/*X�͌Œ�*/
		x = (GAME_SCREEN_X_START>>1)+15;
	for(;i < GAUGE_NUM;i++){
		glPushMatrix();
		/*�����W�̌v�Z*/
		y = (GAME_SCREEN_HEIGHT-(GAME_SCREEN_HEIGHT>>3))-(i*15);
		glTranslatef(x,y,0);
		/*�F�̐ݒ�*/
		if(gauge >= GAUGE_UNIT){		/*�G�l���M�[�Ƃ��Ďg���镪�̕\��*/
			if((FrameCount & 15) < 8)	glColor3f(1.0f , 0.5f , 0.5f);
			else 						glColor3f(1.0f , 0.0f , 0.0f);
		}else{							/*�����g�̕\��*/
			glColor3f(1.0f , 1.0f , 1.0f);
		}
		/*�l�p�̕`��*/
		glBegin(GL_TRIANGLE_FAN);
			glVertex2d(0		,0);
	  		glVertex2d(10.0f	,5.0f);
	  		glVertex2d(10.0f	,-5.0f);
			glVertex2d(0		,-10.0f);
		glEnd();
		if(0 < gauge && gauge < GAUGE_UNIT){			/*�G�l���M�[�Ƃ��Ďg���Ȃ��ʂ̕\��*/
			/*�F�̐ݒ�*/
			glColor3f(1.0f , 0.5f , 0.5f);
			ufloat tmp = (5.0f*gauge)/GAUGE_UNIT;
			glBegin(GL_TRIANGLE_FAN);
				glVertex2d(0		,0);
		  		glVertex2d(10.0f	,+5.0f);
		  		glVertex2d(10.0f	,-tmp);
				glVertex2d(00		,-5.0f-tmp);
			glEnd();
		}
		glPopMatrix();
	gauge-=GAUGE_UNIT;
	}
}
#define MIN_RADIUS 10.0f
#define MAX_RADIUS 50.0f
//#define RADIUS_MAX	4
//static GLfloat Radius[RADIUS_MAX];
//static int RadiusIndex = 0;
void drawShipAttractPowerGauge(){
	static GLfloat radius = MIN_RADIUS;
	/*�͂̎擾*/
	ufloat power = (ufloat)Ship.power / SHIP_POWER_MAX;
	ufloat abs_power = power;
	if(abs_power < 0) abs_power *= -1;
	/*���a�擾*/
	radius -= power/2;
	if(radius > MAX_RADIUS){
		radius = MIN_RADIUS;
	}else if(radius <= MIN_RADIUS){
		radius = MAX_RADIUS;
	}
	/*�F�̐ݒ�*/
	GLfloat color[4];
	if(power > 0){
		color[0] = 1.0f;
		color[1] = color[2] = 1.0f-power;
		color[3] = abs_power;
	}else{
		color[0] = color[1] = 1.0f+power;
		color[2] = 1.0f;
		color[3] = abs_power;
	}
	/*���W�ݒ�*/
	glPoint painted = ShipPaintedPoint;
	painted.radius = radius;
	drawCircle(&painted,color,((radius * 2) / MAX_RADIUS)+1.0f,FALSE);
}
#define LIFE_GAUGE_LENGTH 175
void drawShipLifeGauge(){
	int life = Ship.shield;
	int lifeMax = Ship.shieldMax;
	ufloat color = ((ufloat)(life<<1)/lifeMax) - 1.0f;
	ufloat x,y,length;
	/*�����W�̌v�Z*/
	x = (GAME_SCREEN_X_START>>1)-25;
	y = (GAME_SCREEN_HEIGHT-(GAME_SCREEN_HEIGHT>>3));
	length = (ufloat)(life*LIFE_GAUGE_LENGTH)/(lifeMax);
	//�F�̐ݒ�
	glColor3f(1.0f , 1.0f , 1.0f);
	glPushMatrix();
	glTranslatef(x,y,0);
	/*�l�p�̕`��*/
	glBegin(GL_TRIANGLE_FAN);
		glVertex2d(0		,0);
  		glVertex2d(10.0f, 5.0f);
  		glVertex2d(10.0f, 5.0f - LIFE_GAUGE_LENGTH);
		glVertex2d(	0	,      - LIFE_GAUGE_LENGTH);
	glEnd();
	//�F�̐ݒ�
	glColor3f(1.0-color , 0.0f , color);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2d(0		,0);
  		glVertex2d(10.0f, 5.0f);
  		glVertex2d(10.0f, 5.0f-length);
		glVertex2d(0		,     -length);
	glEnd();
	glPopMatrix();
}
int* FoeOrBossLife;
int FBLifeShownCount;
GLfloat FoeOrBossLifeGaugeColor[][4] = {
	{1.0,0.0,0.0,1.0},//��
	{1.0,0.5,0.0,1.0},//�I�����W
	{0.0,0.5,0.0,1.0},//�[����
	{0.0,0.0,0.5,1.0},//�[����
};
	
#define BOSS_OR_FOE_LIFE_LENGTH (GAME_SCREEN_WIDTH-30)
/*�����W�̌v�Z*/
#define BOSS_OR_FOE_LIFE_X (GAME_SCREEN_X_START+15)
#define BOSS_OR_FOE_LIFE_Y (GAME_SCREEN_HEIGHT >>4)

/*�G�A�������̓{�X�̐����\��*/
void drawFoeOrBossLifeGauge(){
		/*�����������Ȃ̂�`��*/
		/*Alpha����*/
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
		glTranslatef(BOSS_OR_FOE_LIFE_X,BOSS_OR_FOE_LIFE_Y,0);
		/*����̔������*/
		glColor4f(1.0 , 1.0 , 1.0 , 0.3);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2d(0 , 0);
	  		glVertex2d(BOSS_OR_FOE_LIFE_LENGTH	,0);
	  		glVertex2d(BOSS_OR_FOE_LIFE_LENGTH,-2.5f);
			glVertex2d(0, -2.5f);
		glEnd();
		/*�u�����h����*/
		glDisable(GL_BLEND);

		/*�Q�[�W�{��*/
		if(FoeOrBossLife != NULL){
			int shield = max(*FoeOrBossLife,0);
			int div = shield / BOSS_OR_FOE_LIFE_LENGTH;
			shield %= BOSS_OR_FOE_LIFE_LENGTH;
			div = min(3,div);
			if(div > 0){/*��O�̃Q�[�W���A�`����Ȃ�`���B�Ƃ��Ƃ�����B*/
				glColor4fv(&FoeOrBossLifeGaugeColor[div-1][0]);
				glBegin(GL_TRIANGLE_FAN);
					glVertex2d(0 , 0);
			  		glVertex2d(BOSS_OR_FOE_LIFE_LENGTH, 0);
			  		glVertex2d(BOSS_OR_FOE_LIFE_LENGTH, 0-2.5f);
					glVertex2d(0 ,  -2.5f);
				glEnd();
			}			/*�{��*/
			ufloat tmp = shield;
			glColor4fv(&FoeOrBossLifeGaugeColor[div][0]);
			glBegin(GL_TRIANGLE_FAN);
				glVertex2d(0 , 0);
		  		glVertex2d(tmp, 0);
		  		glVertex2d(tmp, -2.5f);
				glVertex2d(0	, -2.5f);
			glEnd();
		}
		glPopMatrix();
		/*1�b�J�E���g���������*/
		FBLifeShownCount++;
		if(FBLifeShownCount > 60){
			FoeOrBossLife = NULL;
		}
}

void setLifeGaugeTarget(int* shield){
	FoeOrBossLife = shield;
	FBLifeShownCount=0;
}

/*�X�R�A*/
#include "include/number.h"

void drawScore(){
	glPoint score_point = {(GAME_SCREEN_X_START+BOSS_OR_FOE_LIFE_LENGTH+8),(GAME_SCREEN_HEIGHT >>4)-12,0,0,0};
	drawNumber(&score_point,0,Score,10);
}
