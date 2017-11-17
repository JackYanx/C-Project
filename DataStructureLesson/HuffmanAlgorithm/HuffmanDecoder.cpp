#include "HuffmanDecoder.h"

HuffmanDecoder::HuffmanDecoder() {

}

void HuffmanDecoder::errMsgDisplay(char* errorMessage) {
	cout << errorMessage;
}

void HuffmanDecoder::build(char* c1, char* c2) {
	zippedFilePath.append(c1);
	originalFilePath.append(c2);
	init();
}

void HuffmanDecoder::init() {

	status = 0;
	//memset(freqList, 0, 256 * sizeof(BinTree*));
	//memset(prefixCode, 0, 256);
	memset(&zipFileHeadTag, 0, sizeof(ZIPFileInfo));
	int i;
	/*
	for (i = 0; i < 256; i++) {
		freqList[i] = new BinTree;
		prefixCode[i] = new char[256];
		memset(freqList[i], 0, sizeof(BinTree));
		memset(prefixCode[i], 0xFF, 256);
		freqList[i]->data = i;
	}
	*/
	if (openFile() != 0) {
		status = -1;
		return;
	}
	if (checkZippedFileValidity() != 0) {
		errMsgDisplay("待解压文件格式有误,请重新选择!\n");
		status = -1;
		return;
	}
	{
		/*文件标签,即"WT"这两个字符*/
		//zipFileHeadTag.zipTag = 0x5457;
		/*文件版本,当前为1.00*/
		//zipFileHeadTag.zipVer = 0x0001;
		/*原文件大小*/
		//zipFileHeadTag.oFileSize = oFileSize;
		/*单条字典记录大小*/
		//zipFileHeadTag.cDictItemSize = sizeof(BinTreeTable);
		/*字典位置偏移量*/
		//zipFileHeadTag.cDictPosi = sizeof(ZIPFileInfo);
	}
}


int HuffmanDecoder::openFile() {
	zippedFile.open(zippedFilePath, ios::in | ios::binary);
	if (!zippedFile.is_open()) {
		errMsgDisplay("原文件打开失败!\n");
		return -1;
	}
	originalFile.open(originalFilePath, ios::out | ios::binary | ios::trunc);
	if (!originalFile.is_open()) {
		errMsgDisplay("创建并写入文件失败!\n");
		return -1;
	}
	zippedFile.seekg(0, zippedFile.end);
	unsigned __int32 fileSize = zippedFile.tellg();
	zFileSize = fileSize;
	return 0;
}

int HuffmanDecoder::checkZippedFileValidity() {
	/*文件大小至少49字节(文件头32字节+至少一条字典记录16字节+文件末尾码1字节)*/
	if (zFileSize < (sizeof(ZIPFileInfo) + sizeof(BinTreeTable) + 1)) {
		errMsgDisplay("文件大小不符合最小压缩文件大小!\n");
		return -1;
	}
	zippedFile.clear();
	zippedFile.seekg(0,ios::beg);
	zippedFile.read((char*)&zipFileHeadTag, sizeof(ZIPFileInfo));
	if (zipFileHeadTag.zipTag != 0x5457) {
		errMsgDisplay("此文件非压缩文件,格式错误\n");
		return -2;
	}
	if (zipFileHeadTag.zipVer != 0x0001) {
		errMsgDisplay("此压缩文件版本过高,暂无法打开\n");
		return -3;
	}
	if (zipFileHeadTag.cFileSize != zFileSize) {
		errMsgDisplay("此压缩文件实际大小与记录不符\n");
		return -4;
	}
	if (zipFileHeadTag.cDataPosi < zipFileHeadTag.cDictPosi + sizeof(BinTreeTable)) {
		errMsgDisplay("........-5\n");
		return -5;
	}
	if (zipFileHeadTag.cDataSize >= zipFileHeadTag.cFileSize || zipFileHeadTag.cDictSize >= zipFileHeadTag.cFileSize) {
		errMsgDisplay("........-6\n");
		return -6;
	}
	if (zipFileHeadTag.cDataSize + zipFileHeadTag.cDictSize + 1 + sizeof(ZIPFileInfo) != zipFileHeadTag.cFileSize) {
		errMsgDisplay("........-7\n");
		return -7;
	}
	if ((unsigned __int32)zipFileHeadTag.cDictItemNumb * zipFileHeadTag.cDictItemSize != zipFileHeadTag.cDictSize) {
		errMsgDisplay("........-8\n");
		return -8;
	}
	if (zipFileHeadTag.cDataPosi != zipFileHeadTag.cDictPosi + zipFileHeadTag.cDictSize) {
		errMsgDisplay("........-9\n");
		return -9;
	}
	if (zipFileHeadTag.cDataPosi + zipFileHeadTag.cDataSize + 1 != zipFileHeadTag.cFileSize) {
		errMsgDisplay("........-10\n");
		return -10;
	}
	if (zipFileHeadTag.cDictPosi != sizeof(ZIPFileInfo)) {
		errMsgDisplay("........-11\n");
		return -11;
	}

	/*应该还有很多严格的判断条件...*/

	return 0;
}

int HuffmanDecoder::checkBinTreeTableValidity() {
	zippedFile.clear();
	zippedFile.seekg(sizeof(ZIPFileInfo), ios::beg);
	zippedFile.read((char*)hfmTreeTable, zipFileHeadTag.cDictSize);
	if (hfmTreeTable[0].par != 0xFF) {
		errMsgDisplay("字典记录哈夫曼码表有误!\n");
		return -1;
	}
	if (hfmTreeTable[0].depth != 1) {
		errMsgDisplay("字典记录哈夫曼码表有误!\n");
		return -2;
	}



	/*应该还有很多严格的判断条件...*/

	return 0;
}