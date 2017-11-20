#pragma once
#include "commen.h"
#include "BinTreeStruct.h"
#include "BinTreeUtils.h"
#include "FileHeadStruct.h"

class HuffmanDecoder {
private:
	string zippedFilePath;
	string originalFilePath;
	ifstream zippedFile;
	ofstream originalFile;
	ZIPFileInfo zipFileHeadTag;
	BinTree* hfmTree;
	BinTreeTable* hfmTreeTable;
	unsigned __int32 zFileSize;
	unsigned __int32 oDataSize;
	int status;
	unsigned char eofTag;

	void errMsgDisplay(char*);
	void init();
	int openFile();
	int checkZippedFileValidity();
	int checkBinTreeTableValidity();


	int getPrefixCodeLen(unsigned char*);
	unsigned char* prefixCodeCat(unsigned char*, unsigned char*);
	unsigned char* trimPrefixCode(unsigned char*, __int32, __int32);
	void getCharFromHfmTree(BinTree*, unsigned char*, unsigned char*, int&, int);
	int readByteStream();
public:
	void build(char*, char*);
	HuffmanDecoder();
	int decode();
};