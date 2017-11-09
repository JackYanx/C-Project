#pragma once
#include "commen.h"
#include "BinTreeStruct.h"
class HuffmanEncoder {
private:
	string src;
	BinTree* hfmTree;
	ostringstream out;
	char* srcarr;
	unsigned __int32 srclen;
	BinTree* freqList[256];
	void generateFreqList();
	int getMinFreqElemSeq();
	int generateHFMTree();
	BinTree* getNewNode();
	BinTree* copyNode(BinTree*);
public:
	HuffmanEncoder();
	void init(string& s);
	int encode();
};