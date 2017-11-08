#pragma once
typedef struct ZIPFileInfoStruct {
	__int32 zipTag;
	__int32 zipVer;
	__int32 reserve1;
	__int32 reserve2;
	unsigned __int32 cFileSize;
	unsigned __int32 cDictSize;
	unsigned __int32 cDictPosi;
	unsigned __int32 cDataSize;
	unsigned __int32 cDataPosi;
	unsigned __int32 oDataSize;
}ZIPFileInfo;