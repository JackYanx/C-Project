#pragma once
typedef unsigned char BinTreeDataType;
typedef struct BinTreeStruct {
	BinTreeStruct* par;
	BinTreeDataType data;
	BinTreeStruct* left;
	BinTreeStruct* right;
	int depth;
}BinTree;