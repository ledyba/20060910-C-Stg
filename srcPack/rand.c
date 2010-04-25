#include <SDL.h>
#include "include/main.h"
#include "include/rand.h"

/*乱数発生*/
static uint Seed;
void srnd(uint seed){
	Seed = seed;
}
uint rnd(){
	uint result;
	Seed *= 214013;
	Seed += 2531011; // ->次に呼び出されたときのseedに使う
	result = Seed;
	result = result >> 0x10;
//	result &= 0xffff;
	return result;
}
