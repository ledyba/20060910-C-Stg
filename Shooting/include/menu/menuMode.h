#define LOAD_TIME_LIMIT 1	//���̃t���[������������܂łɁA���ꂮ�炢�̎��Ԃ��c��
void initMenu();
void quitMenu();
int loadMenu(long next_frame,ARCHIVE* archive);
int finishLoadMenu();
void changeMenuScene(int scene);
void moveMenu();
void drawMenu();
