#include <SDL.h>
#include "include/main.h"
#include "include/rand.h"

/*��������*/
static uint Seed;
void srnd(uint seed){
	Seed = seed;
}
uint rnd(){
	uint result;
	Seed *= 214013;
	Seed += 2531011; // ->���ɌĂяo���ꂽ�Ƃ���seed�Ɏg��
	result = Seed;
	result = result >> 0x10;
//	result &= 0xffff;
	return result;
}
