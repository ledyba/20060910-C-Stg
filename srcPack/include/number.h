#define NUMBER_MAX 1

void initNumber();
int loadNumber(long end_ticks);
int finishLoadNumber();
void quitNumber();

void drawNumber(const glPoint* point,int graphic,unsigned int num,unsigned int digit);
