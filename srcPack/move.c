#include <SDL.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/move.h"
#include "include/ship.h"

/*力によって移動するべき量を計算します．*/
uint moveByForce(Vector* out,Point* pt,uint weight){
			Vector dis;	//距離
			Vector force;//力
			/*距離を取得*/
			dis.x = Ship.pt.x - pt->x;
			dis.y = Ship.pt.y - pt->y;
			dis.speed = sqrti(getDistance2(dis.x,dis.y));
			if(Ship.isShotKeyPressed){
				/*力の取得*/
				getForce(&force,&dis,weight);
				/*撃ってる真っ最中*/
				pt->x += force.x;
				pt->y += force.y;
			}else{
				if(Ship.isPrevShotKeyPressed){
					/*一回押して離した*/
					/*力の取得*/
					getForce(&force,&dis,weight);
						out->x = force.x;
						out->y = force.y;
				}
				/*通常の移動*/
				pt->x += out->x;
				pt->y += out->y;
			}
			return dis.speed << BIT;
}
void getForce(Vector* force,const Vector* dis,uint weight){
			/*力の計算*/
			//定量性の方がやりやすい？
			uint d = dis->speed;//min(dis->speed,200);
			if(Ship.power >= 0){
				force->speed = ((G1*(Ship.power * Ship.power * (d+100)))) / (G2 * weight);
			}else{
				force->speed = -((G2*(Ship.power * Ship.power)*5)) / (G1 * (d+100) *  weight);
			}
//			force->speed = ((G1*(Ship.power * Ship.power * (d+100)))) / (G2 * weight);
			/*パワーがマイナスなら，結果もマイナス*/
//			if(Ship.power < 0)force->speed*=-1;
			uint distance = dis->speed << BIT;
			/*力の速度制限*/
			if(force->speed > distance)force->speed = distance;
			/*力の成分分解*/
			force->x = ((force->speed * dis->x) / (distance + 1));
			force->y = ((force->speed * dis->y) / (distance + 1));
}
/*
//ホーミング軌道を計算する。
void moveByHoming(Vector* source,const Point* pt,const Point* target,uint theta){
	Vector foeVec,rightVec,leftVec;
	//敵への速度ベクトルを取得
	getVector(&foeVec,pt,target,source->speed);
	//右回りの角度制限
	rightVec = *source;
	rotateVector(&rightVec,theta);
	if(source->x * foeVec.x + source->y * foeVec.y 
	>= source->x * rightVec.x + source->y * rightVec.y){		//角度制限チェック
		//範囲内
		*source = foeVec;
	}else{
		//範囲外
		//左回りの角度制限
		leftVec = *source;
		rotateVector(&leftVec,-theta);
		if(foeVec.x * rightVec.x + foeVec.y * rightVec.y
		>= foeVec.x * leftVec.y + foeVec.y * leftVec.y){
			*source = rightVec;
		}else{
			*source = leftVec;
		}
	}
}
*/
