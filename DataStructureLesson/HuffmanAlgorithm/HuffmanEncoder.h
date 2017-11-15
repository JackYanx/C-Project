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
	string src;
	BinTree* hfmTree;
	unsigned char* buf;
	ostringstream out;
	char* srcarr;
	unsigned __int32 srclen;
	BinTree* freqList[256];
	char* prefixCode[256];

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
	void build(char*);
	HuffmanEncoder();
	void init(string& s);
	void init(char*,char*);
	int encode();
};