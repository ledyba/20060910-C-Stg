#define PAD_UP 0x1
#define PAD_DOWN 0x2
#define PAD_LEFT 0x4
#define PAD_RIGHT 0x8
#define PAD_BUTTON_MAX 0x4
#define PAD_BUTTON0 0x10
#define PAD_BUTTON1 0x20
#define PAD_BUTTON2 0x40
#define PAD_BUTTON3 0x80
#define KEY_ESCAPE 0x1000
#define KEY_PAUSE 0x1000
SDL_Joystick *Joystick;
Uint8 *Keys;
uint Input;
uint PrevInput;

#define PAD_UP_INDEX 0
#define PAD_DOWN_INDEX 1
#define PAD_LEFT_INDEX 2
#define PAD_RIGHT_INDEX 3
uint AnalogKey[4];
uint PadShotKey;
uint PadBombKey;

int initInput();
void updateInput();
int getKeyBoardInput();
int getJoystickInput();
int quitInput();
