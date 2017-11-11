#pragma once
#include "commen.h"
#include "BinTreeStruct.h"

extern __int32 getBinTreeNodeNum(BinTree*);

extern __int32 getBinTreeLeavesNum(BinTree*);

extern BinTreeTable* convertTreeToTable(BinTree*);

extern BinTree* convertTableToTree(BinTreeTable*);