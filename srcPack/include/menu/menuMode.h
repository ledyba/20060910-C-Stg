#define LOAD_TIME_LIMIT 1	//次のフレームを準備するまでに、これぐらいの時間を残す
void initMenu();
void quitMenu();
int loadMenu(long next_frame);
int finishLoadMenu();
void changeMenuScene(int scene);
void moveMenu();
void drawMenu();
