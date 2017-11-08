#ifndef FILEMGRUTIL_H
#define FILEMGRUTIL_H

#include "global.h"

#define CONFIG_FILE_FOLDER_PATH   "D:\\"
#define CARD_DATA_FILE_NAME       "cardinfo_"
#define RULE_DATA_FILE_NAME       "rulesinfo_"
#define TO_STAT_FILE_NAME         "toinfo_"
#define SYSTEMLOG_FILE_NAME       "log_"
#define MAX_FILE_FULLPATH         70
#define SYSPATH_SPLIT_CHAR        '\\'

int configFilesInit(unsigned int);
int configFilesSaveTail();
int importDataFromFile();
int exportDataToFile(bool);
int saveLogInfoToFile(SYSLOG*);
char *createFileName(const char*, const char*, unsigned int);
int listAllFilesInCurrentFolder(std::string&);
#endif

