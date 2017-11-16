#pragma once
#include "commen.h"
#include "BinTreeStruct.h"
#include "BinTreeUtils.h"
#include "FileHeadStruct.h"

class HuffmanEncoder {
private:
	string originalFilePath;
	string zippedFilePath;
	ifstream originalFile;
	ofstream zippedFile;
	ZIPFileInfo zipFileHeadTag;
	BinTree* hfmTree;
	BinTree* freqList[256];
	unsigned __int32 oFileSize;
	unsigned __int32 cDataSize;
	int status;
	char* prefixCode[256];
	void init();
	int openFile();
	void generateFreqList();
	int getMinFreqElemSeq();
	int generateHFMTree();
	void writePrefixCodeTable(BinTree*, BinTree*, char*);
	int generatePrefixCodeTable();
	//int getPrefixCodeLen(unsigned char*);
	int writeByteStream();
	BinTree* copyNode(BinTree*);

public:
	void build(char*, char*);
	HuffmanEncoder();
	int encode();
};