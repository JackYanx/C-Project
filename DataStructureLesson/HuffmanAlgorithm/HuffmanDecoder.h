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

	void errMsgDisplay(char*);
	void init();
	int openFile();
	int checkZippedFileValidity();
	int checkBinTreeTableValidity();

public:
	void build(char*, char*);
	HuffmanDecoder();
	int decode();
};