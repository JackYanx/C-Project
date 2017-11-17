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
		errMsgDisplay("����ѹ�ļ���ʽ����,������ѡ��!\n");
		status = -1;
		return;
	}
	{
		/*�ļ���ǩ,��"WT"�������ַ�*/
		//zipFileHeadTag.zipTag = 0x5457;
		/*�ļ��汾,��ǰΪ1.00*/
		//zipFileHeadTag.zipVer = 0x0001;
		/*ԭ�ļ���С*/
		//zipFileHeadTag.oFileSize = oFileSize;
		/*�����ֵ��¼��С*/
		//zipFileHeadTag.cDictItemSize = sizeof(BinTreeTable);
		/*�ֵ�λ��ƫ����*/
		//zipFileHeadTag.cDictPosi = sizeof(ZIPFileInfo);
	}
}


int HuffmanDecoder::openFile() {
	zippedFile.open(zippedFilePath, ios::in | ios::binary);
	if (!zippedFile.is_open()) {
		errMsgDisplay("ԭ�ļ���ʧ��!\n");
		return -1;
	}
	originalFile.open(originalFilePath, ios::out | ios::binary | ios::trunc);
	if (!originalFile.is_open()) {
		errMsgDisplay("������д���ļ�ʧ��!\n");
		return -1;
	}
	zippedFile.seekg(0, zippedFile.end);
	unsigned __int32 fileSize = zippedFile.tellg();
	zFileSize = fileSize;
	return 0;
}

int HuffmanDecoder::checkZippedFileValidity() {
	/*�ļ���С����49�ֽ�(�ļ�ͷ32�ֽ�+����һ���ֵ��¼16�ֽ�+�ļ�ĩβ��1�ֽ�)*/
	if (zFileSize < (sizeof(ZIPFileInfo) + sizeof(BinTreeTable) + 1)) {
		errMsgDisplay("�ļ���С��������Сѹ���ļ���С!\n");
		return -1;
	}
	zippedFile.clear();
	zippedFile.seekg(0,ios::beg);
	zippedFile.read((char*)&zipFileHeadTag, sizeof(ZIPFileInfo));
	if (zipFileHeadTag.zipTag != 0x5457) {
		errMsgDisplay("���ļ���ѹ���ļ�,��ʽ����\n");
		return -2;
	}
	if (zipFileHeadTag.zipVer != 0x0001) {
		errMsgDisplay("��ѹ���ļ��汾����,���޷���\n");
		return -3;
	}
	if (zipFileHeadTag.cFileSize != zFileSize) {
		errMsgDisplay("��ѹ���ļ�ʵ�ʴ�С���¼����\n");
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

	/*Ӧ�û��кܶ��ϸ���ж�����...*/

	return 0;
}

int HuffmanDecoder::checkBinTreeTableValidity() {
	zippedFile.clear();
	zippedFile.seekg(sizeof(ZIPFileInfo), ios::beg);
	zippedFile.read((char*)hfmTreeTable, zipFileHeadTag.cDictSize);
	if (hfmTreeTable[0].par != 0xFF) {
		errMsgDisplay("�ֵ��¼�������������!\n");
		return -1;
	}
	if (hfmTreeTable[0].depth != 1) {
		errMsgDisplay("�ֵ��¼�������������!\n");
		return -2;
	}



	/*Ӧ�û��кܶ��ϸ���ж�����...*/

	return 0;
}