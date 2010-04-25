#ifndef NUMBER_H_
#define NUMBER_H_
#define NUMBER_MAX 1

void initNumber();
int loadNumber(long end_ticks,ARCHIVE* archive);
int finishLoadNumber();
void quitNumber();

void drawNumber(const glPoint* point,int graphic,unsigned int num,unsigned int digit);
void drawNumberA(const glPoint* point,int graphic,unsigned int num,unsigned int digit);

#endif
