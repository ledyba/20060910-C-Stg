#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/shipState.h"
#include "include/gfx/sprite.h"
#include "include/screen.h"
#include "include/ship.h"
#include "include/boss.h"
#include "include/bullet.h"
#include "include/foe.h"
Boss* addBoss(){
	if(boss.state == NOT_EXIST){
		boss.state = EXIST;
		boss.pt.x = (GAME_SCREEN_WIDTH>>1)<<BIT;
		boss.pt.y = (GAME_SCREEN_HEIGHT>>2)<<BIT;
		boss.pt.width = 30 <<BIT;
		boss.pt.height = 30 <<BIT;
		boss.pt.radius = 30 <<BIT;
		boss.shield = 1200;
		boss.laserLockedOn = 0;
		return &boss;
	}else{
		return NULL;
	}
}
void damageBoss(int damage){
	//‘f“_
	Ship_addScore(damage);
	if(boss.state == EXIST){
		setLifeGaugeTarget(&boss.shield);
		boss.shield -= damage;
		if(boss.shield <= 0){
			boss.state = NOT_EXIST;
		}
	}
}
void moveBoss(){
	if(boss.state == EXIST){
		/**/
		boss.pt.x += 0<<BIT;
		boss.pt.y += 0<<BIT;
	}
}
void drawBoss(){
	if(boss.state == EXIST){
		glPoint pt;
		getPaintedPoint(&pt,&boss.pt);
		glColor3f(0.0 , 1.0 , 1.0);
		glPointSize(pt.radius*2);
		glBegin(GL_POINTS);
			glVertex2f(pt.x , pt.y);
		glEnd();
	}
}
