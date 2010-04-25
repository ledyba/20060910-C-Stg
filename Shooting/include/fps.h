#ifndef FPS_H_
#define FPS_H_
void initFps();
int loadFps(long end_ticks,ARCHIVE* archive);
int finishLoadFps();
void quitFPS();

void drawFps();

#define FPS_TEXT_TEXTURE "fps_str.png"

#endif
