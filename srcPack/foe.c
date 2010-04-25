#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/rand.h"
#include "include/point.h"
#include "include/shipState.h"
#include "include/move.h"
#include "include/ship.h"
#include "include/bullet.h"
#include "include/bonus.h"
#include "include/foe.h"
#include "include/boss.h"
#include "include/laser.h"

void initFoe(){
}

Foe* addFoe(){
	int i=0;
	for(;i<FOE_MAX;i++){
		if(foe[i].state == NOT_EXIST){
			foe[i].state = EXIST;
			return &foe[i];
		}
	}
	return NULL;
}

void moveFoe(){
	int i=0;
	/*近さランキングのリセット*/
	resetRanking();
	for(;i<FOE_MAX;i++){
		if(foe[i].state == EXIST){
			Foe* fe = &foe[i];
			/*画面との当たり判定　消えるまでのリミット*/
			if(!isInGameSpace(&fe->pt,50) || fe->limit <= 0){
				fe->state = NOT_EXIST;
				continue;
			}
			/*力が及ぶか？*/
			if(Ship.isTouching) fe->isTouched = TRUE;
			uint dis;
			if(fe->isTouched){
				/*力の及んでいれば，力の影響を受ける*/
				dis = moveByForce(&fe->spd,&fe->pt,fe->weight);
			}else{
				/*そうでなければ，関数ポインタを用いた普通の処理*/
				/*仮*/
				fe->pt.x += fe->spd.x;
				fe->pt.y += fe->spd.y;
				if((fe->limit % 30) == 0){
					Bullet *bt;
					int j=0;
					Vector sh;
					//自機への狙い弾
					getVectorToShip(&sh,&fe->pt,50<<BIT);
					for(j=0;j<5;j++){
						bt = addBullet();
						if(bt != NULL){
						bt->pt.x = fe->pt.x;
						bt->pt.y = fe->pt.y;
						bt->pt.radius = 2 << BIT;
						bt->pt.width = 2 << BIT;
						bt->pt.height = 2 << BIT;
						bt->pt.showWidth = 2 << BIT;
						bt->pt.showHeight = 2 << BIT;
						bt->damage = 1;
						bt->spd = sh;
						//スピードの変更
						changeVectorSpeed(&bt->spd,abs(rnd() % (2<<BIT)) + 256);
						//角度の変更
						rotateVector(&bt->spd,rnd() % 5);
						bt->weight = 400;
						bt->isTouched = FALSE;
						bt->limit = 6000;
						}
					}
				}
				/*距離は求める*/
				uint x = Ship.pt.x - fe->pt.x;
				uint y = Ship.pt.y - fe->pt.y;
				dis = sqrti(getDistance2(x,y)) << BIT;
			}
			/*自機との近さでランキング*/
			sortFoe(&foe[i],dis);
			/*タイムリミットカウント*/
			fe->limit--;
		}
	}
}
void drawFoe(){
	glPoint pt;
	int i=0;
	for(;i<FOE_MAX;i++){
		if(foe[i].state == EXIST){
			getPaintedPoint(&pt,&foe[i].pt);
			glColor3f(0.0 , 1.0 , 0.0);
			glPointSize(pt.radius*2);
			glBegin(GL_POINTS);
				glVertex2f(pt.x , pt.y);
			glEnd();
		}
	}

}
/*ダメージ*/
void damageFoe(Foe* foe,int damage){
	//素点
	Ship_addScore(damage);
	setLifeGaugeTarget(&foe->shield);
	foe->shield -= damage;
	if(foe->shield <= 0){
		/*しぼんぬ*/
		foe->state = NOT_EXIST;
		int i = 0;
		for(;i<BULLET_MAX;i++){
			if(bullet[i].state == EXIST){
				if(isHitSquare(&foe->pt,&bullet[i].pt,foe->pt.radius)){
					bullet[i].state = NOT_EXIST;
					Bonus* bonus = addBonus();
					if(bonus != NULL){
						translateBulletToBonus(bonus,&bullet[i]);
						bonus->pt.radius = 10 << BIT;
						bonus->pt.height = 10 << BIT;
						bonus->pt.width = 10 << BIT;
						bonus->pt.showHeight = 10 << BIT;
						bonus->pt.showWidth = 10 << BIT;
						bonus->weight = 60;
						/*親の状態を反映する*/
						bonus->isTouched = bullet[i].isTouched;
					}
				}
			}
		}
	}
}
typedef struct{
	Foe* foe;
	uint dis;
}FoeList;
/*近さランキング*/
static FoeList FoeRanking[LASER_MAX];
void resetRanking(){
	int i;
	for(i=0;i<LASER_MAX;i++){
		FoeRanking[i].foe = NULL;
		FoeRanking[i].dis = 0;
	}
}
/*並び替え*/
void sortFoe(Foe* foe, uint dis){
	int i;
	for(i=0;i<LASER_MAX;i++){
		if(FoeRanking[i].dis > dis || FoeRanking[i].dis == 0){
			int j = LASER_MAX-1;
			for(;j>i;j--){
				FoeRanking[j].foe = FoeRanking[j-1].foe;
				FoeRanking[j].dis = FoeRanking[j-1].dis;
			}
			FoeRanking[i].foe = foe;
			FoeRanking[i].dis = dis;
			return;	//抜ける。
		}
	}
}
/*近いFoeのリストを取得*/
Foe* getNearistFoe(int num){
	return FoeRanking[num].foe;
}
