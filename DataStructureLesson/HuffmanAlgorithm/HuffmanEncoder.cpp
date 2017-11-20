#include "HuffmanEncoder.h"

void HuffmanEncoder::errMsgDisplay(char* errorMessage) {
	cout << errorMessage;
}

int HuffmanEncoder::openFile() {
	originalFile.open(originalFilePath, ios::in | ios::binary);
	if (!originalFile.is_open()) {
		errMsgDisplay("原文件打开失败!\n");
		return -1;
	}
	zippedFile.open(zippedFilePath, ios::out | ios::binary | ios::trunc);
	if (!zippedFile.is_open()) {
		errMsgDisplay("创建并写入文件失败!\n");
		return -1;
	}
	originalFile.seekg(0, originalFile.end);
	unsigned __int32 fileSize = originalFile.tellg();
	oFileSize = fileSize;
	return 0;
}

void HuffmanEncoder::generateFreqList() {
	unsigned __int32 i;
	unsigned char c;
	originalFile.clear();
	originalFile.seekg(0, ios::beg);
	for (i = 0; i < oFileSize; i++) {
		/*I/O操作,此处有很大的优化空间*/
		originalFile.read((char*)&c, 1);
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

void HuffmanEncoder::build(char* c1, char* c2) {
	originalFilePath.append(c1);
	zippedFilePath.append(c2);
	init();
}

void HuffmanEncoder::init() {

	status = 0;
	memset(freqList, 0, 256 * sizeof(BinTree*));
	memset(prefixCode, 0, 256);
	memset(&zipFileHeadTag, 0, sizeof(ZIPFileInfo));
	int i;
	for (i = 0; i < 256;i++) {
		freqList[i] = new BinTree;
		prefixCode[i] = new char[256];
		memset(freqList[i], 0, sizeof(BinTree));
		memset(prefixCode[i], 0xFF, 256);
		freqList[i]->data = i;
	}
	if (openFile() != 0) {
		status = -1;
		return;
	}

	{
		/*文件标签,即"WT"这两个字符*/
		zipFileHeadTag.zipTag = 0x5457;
		/*文件版本,当前为1.00*/
		zipFileHeadTag.zipVer = 0x0001;
		/*原文件大小*/
		zipFileHeadTag.oFileSize = oFileSize;
		/*单条字典记录大小*/
		zipFileHeadTag.cDictItemSize = sizeof(BinTreeTable);
		/*字典位置偏移量*/
		zipFileHeadTag.cDictPosi = sizeof(ZIPFileInfo);
	}
}
int HuffmanEncoder::generateHFMTree() {
	int min1, min2;
	BinTree* node1, *node2, *temp, *newNode;
	while (true) {
		min1 = getMinFreqElemSeq();
		/*列表中应该至少有一个权重非0的元素,如果没有,说明出错*/
		if (min1 == -1) {
			errMsgDisplay("生成树出现错误!\n");
			return -1;
		}
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
			errMsgDisplay("ERROR!\n");
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
	if (hfmTree->left == NULL && hfmTree->right == NULL && hfmTree->weight != 0) {
		return 0;
	}
	char temp[256];
	memset(temp, 0xFF, 256);
	writePrefixCodeTable(hfmTree, NULL, temp);
	return 0;
}

int HuffmanEncoder::getPrefixCodeLen(unsigned char* p) {
	for (int i = 0; i < 256; i++) {
		if (p[i] == 0xFF) {
			return i;
		}
	}
	return -1;
}

unsigned char* HuffmanEncoder::prefixCodeCat(unsigned char* des, unsigned char* src) {
	__int32 deslen = getPrefixCodeLen(des);
	__int32 srclen = getPrefixCodeLen(src);
	memcpy((des + deslen), src, srclen);
	return des;
}

unsigned char* HuffmanEncoder::trimPrefixCode(unsigned char* des, __int32 desLen, __int32 remain) {
	if (remain == 0) {
		memset(des, 0xFF, 256);
		return des;
	}
	memcpy(des, (des + desLen - remain), remain);
	memset(des + remain, 0xFF, 256 - remain);
	return des;
}

int HuffmanEncoder::writeByteStream() {
	/*当前已转换的原文件字节数*/
	unsigned __int32 cLen = 0;
	/*当前已输出到压缩文件中的编码完成数据字节数*/
	unsigned __int32 eLen = 0;
	/*同来存放临时二进制流为数组*/
	unsigned char tmp[256];
	/*临时数组中有效编码长度,无效编码为0xFF,有效编码为0或者1*/
	__int32 tmplen;
	/*从临时数组中已转换的二进制流bit数*/
	__int32 pLen;
	/*用来参与循环的辅助变量*/
	int i, j;
	/*用来存放读入的字符以及要写入的字符*/
	unsigned char a = 0, b = 0;
	/*用来在临时数组中移动的指针*/
	unsigned char* p = tmp;
	/*两个字符指针*/
	char* q = (char*)&b;
	char* r = (char*)&a;
	/*初始化临时数组内存区域为0xFF*/
	memset(tmp, 0xFF, 256);
	/*清除原文件异常状态,恢复正常状态*/
	originalFile.clear();
	/*定位文件指针到文件开头*/
	originalFile.seekg(0, ios::beg);
	/*清除输出压缩文件文件异常状态,恢复正常状态*/
	zippedFile.clear();
	/*定位文件指针到距离文件开头偏移量为数据偏移位置*/
	zippedFile.seekp(zipFileHeadTag.cDataPosi, ios::beg);
	/*对于只有一种字符的文件,直接跳转到写文件末尾的语句*/
	if (hfmTree->left == NULL && hfmTree->right == NULL && hfmTree->weight != 0)
		goto label;
	/*所读取的原文件字节数小于原文件大小时循环*/
	while (cLen < oFileSize) {
		/*所读取的原文件字节数小于原文件大小且临时数组有效长度小于8时循环*/
		while (cLen < oFileSize && getPrefixCodeLen(tmp) < 8) {
			/*读入一个字节到变量q指针所指变量a中,I/O费时比较严重,这里有优化的空间*/
			originalFile.read(q, 1);
			/*将字符a对应的前缀码拼接到临时数组中*/
			prefixCodeCat(tmp, (unsigned char*)prefixCode[b]);
			/*已读入原文件字节数加一*/
			cLen++;
		}
		/*获取临时数组有效长度*/
		tmplen = getPrefixCodeLen(tmp);
		/*辅助指针p指向临时数组头部*/
		p = tmp;
		/*辅助变量p赋值为临时数组长度*/
		pLen = tmplen;
		/*临时数组中未处理的前缀码数量大于7时循环*/
		while (pLen > 7) {
			/*初始化a为0*/
			a = 0;
			/*截取临时数组中前8位二进制数,转化为一个字节,这里使用位运算提高效率*/
			for (i = 7,j = 0; i > -1; i--,j++) {
				/*使用位运算,每8bit转化为一个char*/
				a += (p[i] << j);
			}
			/*将转化出的这个字节写入压缩文件中,I/O费时比较严重,这里有优化的空间*/
			zippedFile.write(r, 1);
			/*已编码数据长度加一*/
			eLen++;
			/*临时数组中未处理的二进制数长度减8*/
			pLen -= 8;
			/*指针p向后移动8个字节*/
			p += 8;
		}
		/*整理临时数组,使得剩余未转化的二进制数转移到头部*/
		trimPrefixCode(tmp, tmplen, pLen);
	}
	/*变量b赋值为0*/
	b = 0;
	/*处理最后几个bit,不足8bit的剩余部分置为0*/
	if (pLen != 0) {
		a = 0;
		b = pLen;
		p = tmp;
		while (pLen > 0) {
			pLen--;
			a += (p[pLen] << (7 - pLen));
		}
		zippedFile.write(r, 1);
		eLen++;
	}
	label:
	/*写入文件最后一个字节,该字节表示编码好的二进制流不足8bit的剩余部分bit大小,范围0~7*/
	zippedFile.write(q, 1);
	/*压缩后的数据大小*/
	cDataSize = eLen;
	return 0;
}

BinTree* HuffmanEncoder::copyNode(BinTree* node) {
	if (node == NULL) return NULL;
	BinTree* p = new BinTree;
	memcpy(p, node, sizeof(BinTree));
	return p;
}
int HuffmanEncoder::encode() {
	if (status != 0) {
		errMsgDisplay("编码器出错,即将退出...\n");
		return -1;
	}
	generateFreqList();
	if (generateHFMTree() != 0) {
		errMsgDisplay(__FUNCTION__);
	}
	else {
		//cout << "success" << endl << getBinTreeNodeNum(hfmTree) << endl << getBinTreeLeavesNum(hfmTree) << endl;
		setBinTreeDepth(hfmTree, 1);
		BinTreeTable* table = convertTreeToTable(hfmTree);
		BinTree* temp = convertTableToTree(table);
		//cout << compareTree(hfmTree, temp);
		__int16 itemNum = getBinTreeNodeNum(table, 0);

		{
			zipFileHeadTag.cDictItemNumb = itemNum;
			zipFileHeadTag.cDictSize = itemNum * zipFileHeadTag.cDictItemSize;
			zipFileHeadTag.cDataPosi = sizeof(ZIPFileInfo) + zipFileHeadTag.cDictSize;
		}

		{
			zippedFile.clear();
			zippedFile.seekp(0, ios::beg);
			zippedFile.write((char*)&zipFileHeadTag, sizeof(ZIPFileInfo));
			zippedFile.write((char*)table, zipFileHeadTag.cDictSize);
		}
		
		generatePrefixCodeTable();
		writeByteStream();
		zipFileHeadTag.cDataSize = cDataSize;
		zippedFile.seekp(0, ios::end);
		unsigned __int32 cFileSize = zippedFile.tellp();
		zippedFile.seekp(((char*)&zipFileHeadTag.cFileSize - (char*)&zipFileHeadTag), ios::beg);
		zippedFile.write((char*)&cFileSize, sizeof(cDataSize));
		zippedFile.write((char*)&cDataSize, sizeof(cDataSize));
		zippedFile.close();
		if(status == 0)
			cout << "编码成功,压缩文件路径为:" << zippedFilePath << endl << "按回车键继续\n";
		cin.get();
	}

	return 0;
}