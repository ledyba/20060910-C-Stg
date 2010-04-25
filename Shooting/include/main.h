/*弾や敵の状況*/
#define NOT_EXIST 0
#define EXIST 1

int main();
void frameCycle();
int pollEvent();
void init();
void quit();
void move();
void draw();
void raiseError(const char* error ,const char* error2);
void setEndFlag(int isEnd);

unsigned long FrameCount;
long NextTick;

#define GAME_SCENE_MENU	1
#define GAME_SCENE_GAME	2
#define GAME_SCENE_LOADING	3

int GameScene;	//ゲームは今どんなシーンか？

