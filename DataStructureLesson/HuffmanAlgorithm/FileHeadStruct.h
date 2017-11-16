#pragma once
#pragma pack (2)
typedef struct ZIPFileInfoStruct {
	unsigned __int16 zipTag;
	unsigned __int16 zipVer;
	unsigned __int32 oFileSize;
	unsigned __int32 cFileSize;
	unsigned __int32 cDataSize;
	unsigned __int32 cDataPosi;
	unsigned __int32 cDictSize;
	unsigned __int32 cDictPosi;
	unsigned __int16 cDictItemSize;
	unsigned __int16 cDictItemNumb;
}ZIPFileInfo;
#pragma pack ()