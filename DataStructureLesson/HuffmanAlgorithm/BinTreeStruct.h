#pragma once
typedef unsigned char BinTreeDataType;
typedef struct BinTreeDynamicStruct {
	BinTreeDynamicStruct* par;
	BinTreeDynamicStruct* left;
	BinTreeDynamicStruct* right;
	unsigned __int32 weight;
	__int32 depth;
	BinTreeDataType data;
}BinTree;

typedef struct BinTreeStaticStruct {
	__int32 par;
	__int32 left;
	__int32 right;
	__int32 depth;
	unsigned __int32 weight;
	BinTreeDataType data;
}BinTreeTable;