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
	/*撃てるレーザ数を確認*/
	for(i=0;i<LASER_MAX;i++)  if(laser[i].unit[LASER_UNIT_MAX-1].state == NOT_EXIST)left++;
	left = min(left,Ship.gauge/GAUGE_UNIT);
	if(left <= 0)	return;
	/*ターゲット選択。*/
	int locked,leftShield;
	i=0;//インデックスのリセット
	/*ボス*/
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
			/*本数が0ならば抜ける*/
			if(left <= 0)	return;
		}
	}
	/*あまっているので雑魚にまわす*/
	int foeNum;
	Foe* target;
	for(foeNum = 0;foeNum<LASER_MAX;foeNum++){
		target = getNearistFoe(foeNum);
		if(!target)	return;		//敵がレーザの本数未満だったら抜ける
		/*iは初期化しないのがミソ。*/
		leftShield = (target->shield - target->laserLockedOn * LASER_DAMAGE);
		if(leftShield > 0){
			locked = max(1,min(left,(leftShield / LASER_DAMAGE)+1));
			left -= locked;
			for(;i<LASER_MAX && locked > 0;i++,locked--){
				if(addLaser(i,LASER_TARGET_FOE,(void*)target))	{
					Ship.gauge -= GAUGE_UNIT;
				}
			}
			/*本数が0ならば抜ける*/
			if(left <= 0)	return;
		}
	}
}
#define LASER_SPEED (10<<BIT)
static int LaserDefaultCount[6]={0,1,3,5,6,8};
int addLaser(int index,int targetType,void* target){
	if(laser[index].unit[LASER_UNIT_MAX-1].state == NOT_EXIST && target != NULL){
		Laser *lsr = &laser[index];
		/*ターゲットタイプ別設定*/
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
		/*角度制限設定*/
		lsr->count = LaserDefaultCount[index>>1];
		lsr->radLimit = 10;
		/*ターゲットは生きている？*/
		lsr->isTargetAlive = TRUE;
		/*最初の向きの設定*/
		Vector vec;
		/*最初は後ろを向かって発射します。納豆レーザ風味の起動を描きます。*/
		vec.x = 0;
		vec.y = LASER_SPEED;
		vec.speed = LASER_SPEED;
		uint theta;
			if(index & 1){	/*奇数番*/
				theta = index*(-10);
			}else{			/*偶数番*/
				theta = (index+1)*10;
			}
		rotateVector(&vec,theta);//さすがにアレなのでちょっと回転かけます。
		/*ユニット個々の設定*/
		int i;
		LaserUnit *unit = NULL;
		for(i=0;i<LASER_UNIT_MAX;i++){
			unit = &lsr->unit[i];
			/*場所についてはもうちょっとかっこよく・・・。*/
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
			/*ターゲットが生きているかどうかの検証*/
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
			/*レーザを動かす*/
			for(j=0;j<LASER_UNIT_MAX;j++){
				/*指すのが大変なので、ポインタに一回収納する。*/
				LaserUnit *unit = &lsr->unit[j];
				/*新旧の交代*/
				unit->oldPt  = unit->pt;
				unit->oldSpd = unit->spd;
				unit->oldState = unit->state;
				if(unit->state == EXIST){
					if(j == 0){
						if(lsr->count>14){
							/*レーザの先頭の処理*/
							if(lsr->isTargetAlive){	/*ターゲットがまだ生きている*/
								/*ホーミング処理*/
								Vector foeVec,rightVec,leftVec;
								/*敵への速度ベクトルを取得*/
								getVector(&foeVec,&unit->pt,lsr->targetPt,LASER_SPEED);
								/*右回りの角度制限*/
								rightVec = unit->spd;
								rotateVector(&rightVec,lsr->radLimit);
								if(unit->spd.x * foeVec.x + unit->spd.y * foeVec.y 
								>= unit->spd.x * rightVec.x + unit->spd.y * rightVec.y){/*角度制限チェック*/
									/*範囲内*/
									unit->spd = foeVec;
								}else{
									/*範囲外*/
									/*左回りの角度制限*/
									leftVec = unit->spd;
									rotateVector(&leftVec,-lsr->radLimit);
									if(foeVec.x * rightVec.x + foeVec.y * rightVec.y
									>= foeVec.x * leftVec.y + foeVec.y * leftVec.y){
										unit->spd = rightVec;
									}else{
										unit->spd = leftVec;
									}
								}
								/*判定があるのは、先端の一箇所だけ！*/
								if(isHitSquare(lsr->targetPt,&unit->pt,0)){
									unit->state = NOT_EXIST;
									/*ダメージを与える*/
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
							//最初はまず上に飛ばす。斑鳩仕様。
							if((i & 1) != 0)	rotateVector(&unit->spd,-lsr->radLimit);
							else				rotateVector(&unit->spd, lsr->radLimit);
						}

						/*移動*/
						unit->pt.x  += unit->spd.x;
						unit->pt.y  += unit->spd.y;

						/*画面内に存在するか、否か。*/
						if(!isInGameSpace(&unit->pt,100)) unit->state = NOT_EXIST;
					}else{
						/*先頭でないならば、一つ前を追いかける。*/
						unit->pt  = lsr->unit[j-1].oldPt;
						unit->spd = lsr->unit[j-1].oldSpd;
						unit->state = lsr->unit[j-1].oldState;
					}
				}
			}
			/*カウント*/
			lsr->count++;
			/*角度制限をはずす*/
			if(lsr->radLimit < 360 && !(lsr->count & 7) && lsr->count > 30)lsr->radLimit++;
		}
	}
}
void drawLaser(){
	glPoint pt;
	int i,j;
	/*加算合成*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for(i=0;i<LASER_MAX;i++){
		/*それぞれの場所の描画*/
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
