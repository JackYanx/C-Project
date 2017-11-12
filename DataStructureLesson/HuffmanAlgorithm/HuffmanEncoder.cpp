#include "HuffmanEncoder.h"

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
void HuffmanEncoder::init(string& s) {
	src = s;
	srcarr = (char*)s.c_str();
	srclen = s.length();
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

int HuffmanEncoder::generatePrefixCodeTable() {
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
		/*应以二进制打开文件,否则写入0x0A(换行符'\n')时Windows会很智能的写入为0x0D 0x0A('\r\n')*/
		cin.get();
		FILE* fp = fopen("D:\\$111.dat", "wb+");
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