#pragma once
#include "commen.h"
#include "BinTreeStruct.h"
#include "BinTreeUtils.h"
class HuffmanEncoder {
private:
	string src;
	BinTree* hfmTree;
	ostringstream out;
	char* srcarr;
	unsigned __int32 srclen;
	BinTree* freqList[256];
	char* prefixCode[256];
	void generateFreqList();
	int getMinFreqElemSeq();
	int generateHFMTree();
	int generatePrefixCodeTable();
	BinTree* copyNode(BinTree*);

public:
	HuffmanEncoder();
	void init(string& s);
	int encode();
};