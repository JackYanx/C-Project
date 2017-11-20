#pragma once
/*强制编译器使用2字节对齐*/
#pragma pack (2)
typedef struct ZIPFileInfoStruct {
	/*该文件特殊标识,默认为WT两个字符,即16进制0x0x5457*/
	unsigned __int16 zipTag;
	/*压缩软件版本,第一版为0x0001*/
	unsigned __int16 zipVer;
	/*原文件大小,无符号32位整数(即最大4GB)*/
	unsigned __int32 oFileSize;
	/*此压缩文件大小,无符号32位整数(即最大4GB)*/
	unsigned __int32 cFileSize;
	/*此压缩文件中编码好的数据大小,无符号32位整数(即最大4GB)*/
	unsigned __int32 cDataSize;
	/*此压缩文件中编码好的数据偏移量,无符号32位整数*/
	unsigned __int32 cDataPosi;
	/*此压缩文件中哈夫曼编码字典大小,无符号32位整数*/
	unsigned __int32 cDictSize;
	/*此压缩文件中哈夫曼编码字典偏移量,无符号32位整数*/
	unsigned __int32 cDictPosi;
	/*此压缩文件中哈夫曼编码字典单条记录大小,无符号16位整数*/
	unsigned __int16 cDictItemSize;
	/*此压缩文件中哈夫曼编码字典记录数目,无符号16位整数*/
	unsigned __int16 cDictItemNumb;
}ZIPFileInfo;
/*恢复编译器默认对齐设置*/
#pragma pack ()