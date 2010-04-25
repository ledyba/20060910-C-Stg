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
	/*自機を分けるのはここで・・・*/

	/*座標設定*/
	Ship.pt.radius = 2 << BIT;
	Ship.pt.x = (GAME_SCREEN_WIDTH >> 1) << BIT;
	Ship.pt.y = (GAME_SCREEN_HEIGHT-(GAME_SCREEN_HEIGHT >> 2)) << BIT;
	Ship.pt.height = 2 << BIT;
	Ship.pt.width = 2 << BIT;
	/*スピード設定*/
	Ship.spd.x = 3 << BIT;
	Ship.spd.y = 3 << BIT;
	/*残機設定，その他*/
	Ship.shield = 100;
	Ship.shieldMax = 100;
	Ship.power = 0;
	Ship.gauge = 120;
	Score = 0x0;
}


void moveShip(){
	uint spdX = Ship.spd.x;
	uint spdY = Ship.spd.y;
	/*キー入力で自機の移動*/
	if((Input & PAD_UP) != 0 && (Ship.pt.y > ((GAME_SCREEN_HEIGHT << BIT)>>4)))
		Ship.pt.y -= spdY;
	if((Input & PAD_DOWN) != 0 && (Ship.pt.y < ((GAME_SCREEN_HEIGHT<<BIT) - (GAME_SCREEN_HEIGHT <<BIT>> 4))) )
		Ship.pt.y += spdY;
	if((Input & PAD_LEFT) != 0 && (Ship.pt.x > (GAME_SCREEN_WIDTH << BIT)>>4))
		Ship.pt.x -= spdX;
	if((Input & PAD_RIGHT) != 0 && (Ship.pt.x < (GAME_SCREEN_WIDTH << BIT)-(GAME_SCREEN_WIDTH<<BIT>>4)))
		Ship.pt.x += spdX;
	/*前撃っていたかどうかの保存*/
	Ship.isPrevShotKeyPressed = Ship.isShotKeyPressed;
	if(Input & PadShotKey){
		Ship.isShotKeyPressed = TRUE;
	}else{
		Ship.isShotKeyPressed = FALSE;
	}
	if(Ship.isShotKeyPressed){
		if(!Ship.isPrevShotKeyPressed){
			/*前回は押してない = 今回から押し始めた場合*/
			Ship.isTouching = TRUE;
			if(Ship.power < SHIP_POWER_MAX-20)Ship.power+=20;
			else Ship.power = SHIP_POWER_MAX;
		}else{
			/*そうではない場合*/
			Ship.isTouching = FALSE;
		}
		/*ショットボタンを押してるとパワーが増える*/
		if(Ship.power < SHIP_POWER_MAX)Ship.power++;
		if(Ship.shotLimit <= 0){
			/*リミットが0なら弾を撃つ*/
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
			/*弾が撃てない場合はリミットが減る*/
			Ship.shotLimit--;
		}
	}else{
		/*押してないと逆に減る*/
		if(Ship.power >= 1){
			Ship.power--;
		}else if(Ship.power <= -1){
			Ship.power++;
		}
	}
	Ship.isBombShooting = FALSE;
	if(((Input & PadBombKey) && ((PrevInput & PadBombKey) == 0))){/*特殊ボタンを押した（連打必須）*/
		if(Ship.isShotKeyPressed){			/*撃っている最中ならば、力の軽減*/
	/*特殊ボタンを押すとパワーが0になる*/
			if(Ship.gauge-GAUGE_UNIT >= 0){				/*ゲージが撃てる状態である。*/
				Ship.gauge-=GAUGE_UNIT;//ゲージを引く
				if(Ship.power >= 256){					/*ある程度大きいと，0にまで一気に戻す*/
					Ship.isBombShooting = TRUE;
					Ship.power = 0;
				}else if(Ship.power >= -(SHIP_POWER_MAX)){		/*それ以外は普通に減らす*/
					Ship.isBombShooting = TRUE;
					Ship.power -= 256;
					if(Ship.power < -(SHIP_POWER_MAX))Ship.power = -(SHIP_POWER_MAX);
				}
			}
		}else{
			/*ホーミングレーザ*/
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
/*ダメージを与える*/
void Ship_addDamage(int damage){
	if(Ship.shield > 0)
	Ship.shield -= damage;
}
unsigned long lastBonusTime;	//最後にいつボーナスを取得したか？
/*ボーナスダメージの取得*/
void Ship_getBonus(){
	/*差の取得*/
	unsigned long diff = FrameCount - lastBonusTime;
	if(diff == 0)diff = 1;
	/*更新*/
	lastBonusTime = FrameCount;
	/*スコア処理*/
	Score += SHIP_MAX_BONUS / diff;
	/*ホーミングレーザ処理*/
	if(Ship.gauge < GAUGE_MAX) Ship.gauge++;
}
void Ship_addScore(unsigned int score){
	Score += score;
}
