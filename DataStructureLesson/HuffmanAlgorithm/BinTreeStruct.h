#pragma once
typedef unsigned char BinTreeDataType;
typedef struct BinTreeDynamicStruct {
	BinTreeDynamicStruct* par;
	BinTreeDynamicStruct* left;
	BinTreeDynamicStruct* right;
	unsigned __int32 weight;
	__int16 depth;
	BinTreeDataType data;
}BinTree;
#pragma pack(2)
typedef struct BinTreeStaticStruct {
	__int16 par;
	__int16 left;
	__int16 right;
	__int16 depth;
	unsigned __int32 weight;
	BinTreeDataType data;
	char reserve1;
	char reserve2;
	char reserve3;
}BinTreeTable;
#pragma pack()