#define CONFIG_FILE	"config.sav"
struct{
	int ShotKeyButton;
	int BombKeyButton;
}ConfigData;

void initConfig();
int setConfig();
int loadConfig();
int saveConfig();
int makeNewConfigFile();
