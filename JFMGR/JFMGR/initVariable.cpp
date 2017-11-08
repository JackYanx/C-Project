#include "initVariable.h"

/*需要初始化的相关全局变量*/
Card* headCard;
Card* currentCard;
OnlineUser* headOU;
OnlineUser* currentOU;
Rule* headRule;
Rule* currentRule;
SYSLOG* LogInfo;
unsigned currentRuleRating;
int onlineCount;
int maxOnlineCount;
int totalCount;
unsigned int initSystemTime;
unsigned int totalUserChargeMoney;
unsigned int totalUserConsumeMoney;
char* cardDataPath;
char* rulesDataPath;
char* toSataPath;
char* systemLogPath;