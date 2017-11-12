#pragma once
#include "commen.h"
#include "BinTreeStruct.h"

extern __int16 getBinTreeNodeNum(BinTree*);

extern __int16 getBinTreeLeavesNum(BinTree*);

extern __int16 getBinTreeNodeNum(BinTreeTable*, __int16);

extern __int16 getBinTreeLeavesNum(BinTreeTable*, __int16);

extern BinTreeTable* convertTreeToTable(BinTree*);

extern BinTree* convertTableToTree(BinTreeTable*);

extern BinTree* getNewNode();

extern __int16 getBinTreeDepth(BinTree*);

extern __int16 getBinTreeDepth(BinTreeTable*);

extern void setBinTreeDepth(BinTree*, __int16);

extern void setBinTreeDepth(BinTreeTable*, __int16, __int16);

extern __int16 compareTree(BinTree*, BinTree*);

extern __int16 compareTree(BinTree*, BinTreeTable*);

extern __int16 compareTree(BinTreeTable*, BinTree*);

extern __int16 compareTree(BinTreeTable*, BinTreeTable*);

extern __int16 destoryBinTree(BinTree*);

extern __int16 destoryBinTree(BinTreeTable*&);