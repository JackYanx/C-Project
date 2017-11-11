#pragma once
#include "commen.h"
#include "BinTreeStruct.h"

extern __int32 getBinTreeNodeNum(BinTree*);

extern __int32 getBinTreeLeavesNum(BinTree*);

extern __int32 getBinTreeNodeNum(BinTreeTable*, __int32);

extern __int32 getBinTreeLeavesNum(BinTreeTable*, __int32);

extern BinTreeTable* convertTreeToTable(BinTree*);

extern BinTree* convertTableToTree(BinTreeTable*);

extern BinTree* getNewNode();

extern __int32 getBinTreeDepth(BinTree*);

extern __int32 getBinTreeDepth(BinTreeTable*);

extern void setBinTreeDepth(BinTree*, __int32);

extern void setBinTreeDepth(BinTreeTable*, __int32, __int32);

extern __int32 compareTree(BinTree*, BinTree*);

extern __int32 compareTree(BinTree*, BinTreeTable*);

extern __int32 compareTree(BinTreeTable*, BinTree*);

extern __int32 compareTree(BinTreeTable*, BinTreeTable*);

extern __int32 destoryBinTree(BinTree*);

extern __int32 destoryBinTree(BinTreeTable*&);