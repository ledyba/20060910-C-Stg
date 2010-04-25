/*���[�h��ʂ̊Ǘ����s��*/

#define LOAD_ARCHIVE "load.arc"
#define LOAD_BG "LoadBG.png"

 typedef struct{
 	void (*init)();
 	int (*load)(long);
 	int (*finish)();
 	void (*quit)();
 }LOAD_FUNCS;

/*���[�h�̏���*/
void initLoad();
/*���[�h��ʂ̏����E�I��*/
void setLoad(int funcs,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode);
void startLoad();
void quitLoad();
/*������*/
void moveLoad();
/*�`�ʂ���*/
void drawLoad();

