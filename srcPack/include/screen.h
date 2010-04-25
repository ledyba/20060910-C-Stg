#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    32
#define WINDOW_TITLE "Title–¢’è"


int initSDL();
int quitSDL();
void drawBlackBackground();
void drawSideBar();
void drawCursor(glPoint* point,GLfloat  size,const GLfloat* color,int isRight);
void drawBox(glPoint* point,int isFilled,float width,const GLfloat* color);
void drawCircle(const glPoint* point,const GLfloat* color,float width,int isFilled);
