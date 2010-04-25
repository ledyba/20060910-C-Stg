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
static int EndFlag = FALSE;		//ゲーム終了フラグ

int main(int argc,char *argv[]){
	/*ライブラリ初期化*/
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
	/*音楽の準備のテスト*/
	/*
	if(!loadMusic("pxtone\\no name.ptcop")){
		fprintf(stderr,"failed to load Music.\n");
	}
	if(!playMusic(0,0)){
		fprintf(stderr,"failed to play Music.\n");
	}
	*/
	/*ゲームの前準備*/
	init();
	/*ゲーム本体のルーチン*/
	frameCycle();
	/*終了処理*/
	quit();
	return 0;
}
/**
 * 1フレームの管理を行います．
 */
void frameCycle(){
	int done = 1;
	long nextTickCount = SDL_GetTicks();
	long leftTickCount = 0;
	FrameCount = 0;
	while(done){
		/*フレームカウント*/
		FrameCount++;
		/*次のフレームの時間を取得する*/
		nextTickCount += FRAME_LIMIT;
		NextTick = nextTickCount;
		/*キー状態の取得*/
		updateInput();
		/*続けるか否かの取得*/
		done &= pollEvent();
		done &= (EndFlag==FALSE);
		/*移動・あたり判定*/
		move();
	/*たまにフレームが落ちる．しょうがないのかなぁ・・・．*/
		leftTickCount = nextTickCount - (long)SDL_GetTicks();
		if(leftTickCount > 0){
			/*フレームに余裕があれば，描写の処理*/
			draw();
			leftTickCount = nextTickCount - (long)SDL_GetTicks();
			/*まだ余裕があれば待つ*/
			if(leftTickCount > 0){
				SDL_Delay(leftTickCount);
			}
		}
	}
}

#define INIT_LOAD_FUNC_NUM 2
//最初の読み込み用関数群
LOAD_FUNCS InitLoadFuncs[INIT_LOAD_FUNC_NUM] = {
	{initMenu,loadMenu,finishLoadMenu},
	{initCommon,loadCommon,finishLoadCommon},
};
/* ゲーム全体の初期化です*/
void init(){
	initConfig();														//設定読み込み
	srnd(3100);															//乱数初期化
	initShipState();													//ステータス表示
	initPoint();														//座標変換ライブラリ
	initLoad();															//ロードライブラリ
	setLoad(INIT_LOAD_FUNC_NUM,NULL,NULL,&InitLoadFuncs[0],GAME_SCENE_MENU);	//メニュー開始
}
/*ゲーム全体の終了処理*/
void quit(){
	/*メモリ開放とか、とか。*/
	quitCommon();
	quitLoad();
	quitMenu();
	quitSDL();
	quitInput();
}
/**
 * 敵や自機等を動かします．
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
 * 敵や自機を描写します．
 */
void draw(){
	/*黒く塗る*/
	//if((FrameCount & 7)==0)		//不思議な効果になる.
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
			drawSideBar();		//黒い両サイドバー
			drawShipState();
			break;
		case GAME_SCENE_LOADING:
			drawLoad();
			break;
	}
	drawFps();
	// 画面を更新します
//	glFinish();//CPU占領率は100%になっちゃうんですけどね・・・。
//	glFlush();//なぜか糞重い・・・。
	SDL_GL_SwapBuffers();
}

/**
 * イベント処理
 * 戻り値：続けてよいなら１
 */
int pollEvent()
{
	SDL_Event ev;
	while(SDL_PollEvent(&ev) ){
		/*終了処理*/
		if(ev.type == SDL_QUIT || ((Input & KEY_ESCAPE) != 0)){
			return FALSE;
		}
		/*ポーズイベント*/
		
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
