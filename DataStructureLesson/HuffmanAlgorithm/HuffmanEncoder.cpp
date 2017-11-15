#include "HuffmanEncoder.h"
unsigned char buff[102400];

int HuffmanEncoder::openFile() {
	originalFile.open(originalFilePath, ios::in | ios::binary);
	if (!originalFile.is_open()) {
		cout << "原文件打开失败!\n";
		return -1;
	}
	zippedFile.open(zippedFilePath, ios::out | ios::binary);
	if (!zippedFile.is_open()) {
		cout << "创建并写入文件失败!\n";
		return -1;
	}
	originalFile.seekg(0, originalFile.end);
	unsigned __int32 fileSize = originalFile.tellg();
}

void HuffmanEncoder::generateFreqList() {
	unsigned __int32 i;
	unsigned char c;
	for (i = 0; i < srclen; i++) {
		c = (unsigned char)srcarr[i];
		freqList[c]->weight++;
	}
}
int HuffmanEncoder::getMinFreqElemSeq() {
	BinTree* node = NULL;
	int i,j,k;
	int pos = 0;
	unsigned __int32 minWeight = 0xFFFFFFFF;
	unsigned __int32 curWeight = 0;
	for (j = 0,k = 0; j < 256;j++) {
		if (freqList[j]->weight != 0) {
			k = 1;
			break;
		}
	}
	if (k == 0) return -1;
	for (i = 0; i < 256; i++) {
		curWeight = freqList[i]->weight;
		if (curWeight != 0 && minWeight > curWeight) {
			minWeight = curWeight;
			pos = i;
		}
	}
	return pos;
}
HuffmanEncoder::HuffmanEncoder() {

}

void HuffmanEncoder::build(char*, char*) {

}

void HuffmanEncoder::build(char*) {

}

void HuffmanEncoder::init(string& s) {
	src = s;
	srcarr = (char*)s.c_str();
	srclen = s.length();
	buf = buff;
	memset(buf, 0, 102400);
	memset(freqList, 0, 256 * sizeof(BinTree*));
	memset(prefixCode, 0, 256);
	int i;
	for (i = 0; i < 256;i++) {
		freqList[i] = new BinTree;
		prefixCode[i] = new char[256];
		memset(freqList[i], 0, sizeof(BinTree));
		memset(prefixCode[i], 0xFF, 256);
		freqList[i]->data = i;
	}
	int i1 = 1;
}
int HuffmanEncoder::generateHFMTree() {
	int min1, min2;
	BinTree* node1, *node2, *temp, *newNode;
	while (true) {
		min1 = getMinFreqElemSeq();
		/*列表中应该至少有一个权重非0的元素,如果没有,说明出错*/
		if (min1 == -1) return -1;
		node1 = copyNode(freqList[min1]);
		freqList[min1]->weight = 0;

		min2 = getMinFreqElemSeq();
		/*当min2为-1时,树生成完成*/
		if (min2 == -1) {
			hfmTree = node1;
			return 0;
		}
		temp = freqList[min2];
		node2 = copyNode(temp);
		freqList[min2]->weight = 0;

		newNode = getNewNode();
		node1->par = newNode;
		node2->par = newNode;
		newNode->left = node1;
		newNode->right = node2;
		newNode->weight = node1->weight + node2->weight;
		delete temp;
		freqList[min2] = newNode;
	}
	return -2;
}

void HuffmanEncoder::writePrefixCodeTable(BinTree* node, BinTree* par, char* temp) {
	if (node == NULL || temp == NULL) return;
	if (par != NULL) {
		__int32 seq = (node->depth) - 2;
		if (node == par->left) {
			temp[seq] = 0;
		}
		else if(node == par->right){
			temp[seq] = 1;
		}
		else {
			cout << "ERROR!\n";
			return;
		}
	}
	if (node->left == NULL && node->right == NULL) {
		memcpy(prefixCode[node->data], temp, node->depth-1);
		return;
	}
	writePrefixCodeTable(node->left, node, temp);
	writePrefixCodeTable(node->right, node, temp);
}

int HuffmanEncoder::generatePrefixCodeTable() {
	char temp[256];
	memset(temp, 0xFF, 256);
	writePrefixCodeTable(hfmTree, NULL, temp);
	return 0;
}

int getPrefixCodeLen(unsigned char* p) {
	for (int i = 0; i < 256; i++) {
		if (p[i] == 0xFF) {
			return i;
		}
	}
	return -1;
}

unsigned char* prefixCodeCat(unsigned char* des, unsigned char* src) {
	__int32 deslen = getPrefixCodeLen(des);
	__int32 srclen = getPrefixCodeLen(src);
	memcpy((des + deslen), src, srclen);
	return des;
}

unsigned char* trimPrefixCode(unsigned char* des, __int32 desLen, __int32 remain) {
	if (remain == 0) {
		memset(des, 0xFF, 256);
		return des;
	}
	memcpy(des, (des + desLen - remain), remain);
	memset(des + remain, 0xFF, 256 - remain);
	return des;
}

int HuffmanEncoder::writeByteStream() {
	unsigned __int32 cLen = 0;
	unsigned __int32 eLen = 0;
	unsigned char tmp[256];
	__int32 tmplen;
	__int32 pLen;
	__int32 scale;
	unsigned char* p = tmp;
	unsigned char a;
	memset(tmp, 0xFF, 256);
	while (cLen < srclen) {
		while (cLen < srclen && getPrefixCodeLen(tmp) < 8) {
			prefixCodeCat(tmp, (unsigned char*)prefixCode[(unsigned char)srcarr[cLen]]);
			cLen++;
		}
		
		tmplen = getPrefixCodeLen(tmp);
		p = tmp;
		pLen = tmplen;
		while (pLen > 7) {
			a = 0;
			scale = 1;
			for (int i = 7; i > -1; i--) {
				a += p[i] * scale;
				scale *= 2;
			}
			buf[eLen] = a;
			eLen++;
			pLen -= 8;
			p += 8;
		}
		trimPrefixCode(tmp, tmplen, pLen);
	}
	/*处理最后几个bit,不足8bit的剩余部分置为0*/
	//while (pLen > 0) {

	//}
	return 0;
}

BinTree* HuffmanEncoder::copyNode(BinTree* node) {
	if (node == NULL) return NULL;
	BinTree* p = new BinTree;
	memcpy(p, node, sizeof(BinTree));
	return p;
}
int HuffmanEncoder::encode() {
	generateFreqList();
	if (generateHFMTree() != 0) {
		cout << __FUNCTION__;
	}
	else {
		cout << "success" << endl << getBinTreeNodeNum(hfmTree) << endl << getBinTreeLeavesNum(hfmTree) << endl;
		setBinTreeDepth(hfmTree, 1);
		BinTreeTable* table = convertTreeToTable(hfmTree);
		//cout << getBinTreeNodeNum(table, 0) << endl << getBinTreeLeavesNum(table, 0) << endl << getBinTreeDepth(hfmTree) << endl;
		BinTree* temp = convertTableToTree(table);
		//cout << "+++" << getBinTreeNodeNum(temp) << endl << getBinTreeLeavesNum(temp) << endl << getBinTreeDepth(table) << endl;
		cout << compareTree(hfmTree, temp);
		generatePrefixCodeTable();
		writeByteStream();
		/*应以二进制打开文件,否则写入0x0A(换行符'\n')时Windows会很智能的写入为0x0D 0x0A('\r\n')*/
		cin.get();
		FILE* fp = fopen("D:\\$111.dat", "wb+");
		FILE* fp2 = fopen("D:\\aaaaa.txt", "r+");
		char aaa[222];
		fread(aaa, 1, 1, fp2);
		if (fp == NULL) {
			cout << "OPEN FAILED!\n";
		}
		else {
			cout << "OPEN SUCCEEDED!\n";
			fwrite(table, sizeof(BinTreeTable), getBinTreeNodeNum(table, 0), fp);
			fflush(fp);
			fclose(fp);
		}
	}

	return 0;
}