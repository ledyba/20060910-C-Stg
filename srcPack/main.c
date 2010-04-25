#include <SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>

#include "include/main.h"
#include "include/rand.h"
#include "include/input.h"
#include "include/music.h"
#include "include/point.h"
#include "include/gfx/sprite.h"
#include "include/screen.h"
//#include "include/move.h"
#include "include/ship.h"
#include "include/shot.h"
#include "include/bullet.h"
#include "include/bonus.h"
#include "include/foe.h"
#include "include/boss.h"
#include "include/laser.h"
#include "include/shipState.h"
#include "include/load.h"

#include "include/data/config.h"
#include "include/menu/menu.h"
#include "include/menu/menuMode.h"

#include "include/stage/eventGenerator.h"
#include "include/fps.h"
#include "include/data/buf.h"
#include "include/data/data.h"
#include "include/common.h"

//static int WindowMode;
static int EndFlag = FALSE;		//�Q�[���I���t���O

int main(int argc,char *argv[]){
	/*���C�u����������*/
	if(!initSDL(0)){
		raiseError("failed to prepare SDL libs.","\n");
	}
	if(!initInput()){
		raiseError("failed to prepare INPUT libs.","\n");
	}
	/*
	if(!initMusic()){
		raiseError("failed to prepare MUSIC libs.","\n");
	}
	*/
	/*���y�̏����̃e�X�g*/
	/*
	if(!loadMusic("pxtone\\no name.ptcop")){
		fprintf(stderr,"failed to load Music.\n");
	}
	if(!playMusic(0,0)){
		fprintf(stderr,"failed to play Music.\n");
	}
	*/
	/*�Q�[���̑O����*/
	init();
	/*�Q�[���{�̂̃��[�`��*/
	frameCycle();
	/*�I������*/
	quit();
	return 0;
}
/**
 * 1�t���[���̊Ǘ����s���܂��D
 */
void frameCycle(){
	int done = 1;
	long nextTickCount = SDL_GetTicks();
	long leftTickCount = 0;
	FrameCount = 0;
	while(done){
		/*�t���[���J�E���g*/
		FrameCount++;
		/*���̃t���[���̎��Ԃ��擾����*/
		nextTickCount += FRAME_LIMIT;
		NextTick = nextTickCount;
		/*�L�[��Ԃ̎擾*/
		updateInput();
		/*�����邩�ۂ��̎擾*/
		done &= pollEvent();
		done &= (EndFlag==FALSE);
		/*�ړ��E�����蔻��*/
		move();
	/*���܂Ƀt���[����������D���傤���Ȃ��̂��Ȃ��E�E�E�D*/
		leftTickCount = nextTickCount - (long)SDL_GetTicks();
		if(leftTickCount > 0){
			/*�t���[���ɗ]�T������΁C�`�ʂ̏���*/
			draw();
			leftTickCount = nextTickCount - (long)SDL_GetTicks();
			/*�܂��]�T������Α҂�*/
			if(leftTickCount > 0){
				SDL_Delay(leftTickCount);
			}
		}
	}
}

#define INIT_LOAD_FUNC_NUM 2
//�ŏ��̓ǂݍ��ݗp�֐��Q
LOAD_FUNCS InitLoadFuncs[INIT_LOAD_FUNC_NUM] = {
	{initMenu,loadMenu,finishLoadMenu},
	{initCommon,loadCommon,finishLoadCommon},
};
/* �Q�[���S�̂̏������ł�*/
void init(){
	initConfig();														//�ݒ�ǂݍ���
	srnd(3100);															//����������
	initShipState();													//�X�e�[�^�X�\��
	initPoint();														//���W�ϊ����C�u����
	initLoad();															//���[�h���C�u����
	setLoad(INIT_LOAD_FUNC_NUM,NULL,NULL,&InitLoadFuncs[0],GAME_SCENE_MENU);	//���j���[�J�n
}
/*�Q�[���S�̂̏I������*/
void quit(){
	/*�������J���Ƃ��A�Ƃ��B*/
	quitCommon();
	quitLoad();
	quitMenu();
	quitSDL();
	quitInput();
}
/**
 * �G�⎩�@���𓮂����܂��D
 */
void move(){
		switch(GameScene){
			case GAME_SCENE_MENU:
				moveMenu();
				break;
			case GAME_SCENE_GAME:
				if(FrameCount % 20 == 0){
					Foe *fe;
					fe = addFoe();
					if(fe != NULL){
					fe->pt.x = abs(rnd() % GAME_SCREEN_WIDTH)<<BIT;
					fe->pt.y = abs(rnd() % (GAME_SCREEN_HEIGHT >> 2))<<BIT;
					fe->pt.radius = 20 << BIT;
					fe->pt.width = 20 << BIT;
					fe->pt.height = 20 << BIT;
					fe->pt.showWidth = 20 << BIT;
					fe->pt.showHeight = 20 << BIT;
					fe->spd.x = 0;
					fe->spd.y = 0;
					fe->weight = 200;
					fe->shield = 4;
					fe->laserLockedOn = 0;
					fe->damage = 1;
					fe->isTouched = FALSE;
					fe->limit = 3000;
					}
				}
				moveShip();
				moveBonus();
				moveShot();
				moveLaser();
				moveFoe();
				moveBoss();
				moveBullet();
				break;
			case GAME_SCENE_LOADING:
				moveLoad();
				break;
		}
}
/**
 * �G�⎩�@��`�ʂ��܂��D
 */
void draw(){
	/*�����h��*/
	//if((FrameCount & 7)==0)		//�s�v�c�Ȍ��ʂɂȂ�.
	drawBlackBackground();
	switch(GameScene){
		case GAME_SCENE_MENU:
			drawMenu();
			break;
		case GAME_SCENE_GAME:
			drawBonus();
			drawShot();
			drawFoe();
			drawBoss();
			drawLaser();
			drawShip();
			drawBullet();
			drawSideBar();		//�������T�C�h�o�[
			drawShipState();
			break;
		case GAME_SCENE_LOADING:
			drawLoad();
			break;
	}
	drawFps();
	// ��ʂ��X�V���܂�
//	glFinish();//CPU��̗���100%�ɂȂ����Ⴄ��ł����ǂˁE�E�E�B
//	glFlush();//�Ȃ������d���E�E�E�B
	SDL_GL_SwapBuffers();
}

/**
 * �C�x���g����
 * �߂�l�F�����Ă悢�Ȃ�P
 */
int pollEvent()
{
	SDL_Event ev;
	while(SDL_PollEvent(&ev) ){
		/*�I������*/
		if(ev.type == SDL_QUIT || ((Input & KEY_ESCAPE) != 0)){
			return FALSE;
		}
		/*�|�[�Y�C�x���g*/
		
	}
	return TRUE;
}

void raiseError(const char* error ,const char* error2){
	fprintf(stderr,error);
	fprintf(stderr,error2);
	fprintf(stderr,"\n");
	quit();
	exit(0);
}
void setEndFlag(int isEnd){
	EndFlag = isEnd;
}
