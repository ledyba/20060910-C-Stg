/*ロード画面の管理を行う*/

#define LOAD_ARCHIVE "load.arc"
#define LOAD_BG "LoadBG.png"

 typedef struct{
 	void (*init)();
 	int (*load)(long);
 	int (*finish)();
 	void (*quit)();
 }LOAD_FUNCS;

/*ロードの準備*/
void initLoad();
/*ロード画面の準備・終了*/
void setLoad(int funcs,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode);
void startLoad();
void quitLoad();
/*動かす*/
void moveLoad();
/*描写する*/
void drawLoad();

