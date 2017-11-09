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
	int i;
	unsigned char pos = 0;
	BinTreeDataType minWeight = 255;//freqList[0]->weight;
	BinTreeDataType curWeight = 0;
	for (i = 0; i < 256; i++) {
		curWeight = freqList[(unsigned char)i]->weight;
		if (curWeight != 0 && minWeight > curWeight) {
			minWeight = curWeight;
			pos = (unsigned char)i;
		}
	}
	if (minWeight != 0) {
		return pos;
	}
	return -1;
}
HuffmanEncoder::HuffmanEncoder() {

}
void HuffmanEncoder::init(string& s) {
	src = s;
	srcarr = (char*)s.c_str();
	srclen = s.length();
	memset(freqList, 0, 256 * sizeof(BinTree*));
	int i;
	for (i = 0; i < 256;i++) {
		freqList[i] = new BinTree;
		memset(freqList[i], 0, sizeof(BinTreeStruct));
		freqList[i]->data = (unsigned char)i;
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
BinTree* HuffmanEncoder::getNewNode() {
	BinTree* p = new BinTree;
	memset(p, 0, sizeof(BinTree));
	return p;
}
BinTree* HuffmanEncoder::copyNode(BinTree* node) {
	if (node == NULL) return NULL;
	BinTree* p = new BinTree;
	memcpy(p, node, sizeof(BinTree));
}
int HuffmanEncoder::encode() {
	generateFreqList();
	if (generateHFMTree() != 0) {
		cout << __FUNCTION__;
	}

	return 0;
}