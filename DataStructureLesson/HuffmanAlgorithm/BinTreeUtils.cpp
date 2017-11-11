#include "BinTreeUtils.h"

__int32 getBinTreeNodeNum(BinTree* tree) {
	if (tree == NULL) return 0;
	return getBinTreeNodeNum(tree->left) + getBinTreeNodeNum(tree->right) + 1;
}

__int32 getBinTreeLeavesNum(BinTree* tree) {
	if (tree == NULL) return 0;
	if (tree->left == NULL && tree->right == NULL) return 1;
	return getBinTreeLeavesNum(tree->left) + getBinTreeLeavesNum(tree->right);
}

void writeTable(BinTreeTable* table, BinTree* tree, __int32& seq, __int32 par) {
	if (table == NULL || tree == NULL) return;
	__int32 cur = seq;
	table[cur].data = tree->data;
	table[cur].weight = tree->weight;
	table[cur].depth = tree->depth;
	table[cur].par = par;
	if (tree->left != NULL) {
		seq++;
		table[cur].left = seq;
		writeTable(table, tree->left, seq, cur);
	}
	else {
		table[cur].left = -1;
	}
	if (tree->right != NULL) {
		seq++;
		table[cur].right = seq;
		writeTable(table, tree->right, seq, cur);
	}
	else {
		table[cur].right = -1;
	}
}

BinTreeTable* convertTreeToTable(BinTree* tree) {
	__int32 num = getBinTreeNodeNum(tree);
	BinTreeTable* table = new BinTreeTable[num];
	__int32 i = 0;
	writeTable(table, tree, i, -1);
	return table;
	/*
	__int32 num = getBinTreeNodeNum(tree);
	BinTreeTable table[11];//= new BinTreeTable[num];
	__int32 i = 0;
	writeTable(table, tree, i, 0);
	
	*/
}

BinTree* convertTableToTree(BinTreeTable* table) {
	return NULL;
}