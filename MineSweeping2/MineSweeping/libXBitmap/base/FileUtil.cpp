#include "FileUtil.h"

std::ifstream fz;
uXBMInt16 BM_tag;
uXBMInt32 BM_size;
int openXBMFile(const char* filePath, std::fstream* fin) {
	uXBMInt32 fLength = getFileSize(filePath);
	if (fLength < 50) {
		return 0;
	}
	fz.open(filePath, std::ios::binary);
	if (!fz.is_open()) {
		return 0;
	}

	fz.read((char*)&BM_tag, 2);
	fz.read((char*)&BM_size,4);
	if (BM_tag != 0x4D42 || BM_size != fLength) {
		fz.close();
		return 0;
	}
	fz.close();
	fin->open(filePath, std::ios::binary|std::ios::in);
	return 1;
}

int checkXBMDataValidity(BitmapFileHeader* bfh, BitmapInfo* bi, BitmapPalette* bp) {
	bool val = ((bfh->bfReserved == 0) && (bi->biPlanes == 1) && (bi->biWidthPix > 0));
	if (!val) {
		return 0;
	}
	int compressionStatus = checkXBMDataCompression(bi);
	if (compressionStatus != 0) {
		if (compressionStatus == -1) {
			return 0;
		}
		//TODO 解压操作
		/*
		DecompressData();
		*/
		return 0;
	}
	int bitPerPixStatus = checkXBMBit(bi);
	if (bitPerPixStatus != 1) {
		if (bitPerPixStatus != 0) {
			return 0;
		}
		//TODO 使用调色板处理索引数据
		/*
		DecodeRGBQUAD();
		*/
		return 0;
	}
	return 1;
}

int checkXBMBit(BitmapInfo* bi) {
	uXBMInt16 bitCountPerPix = bi->biBitCountPerPix;
	if (bitCountPerPix == 24 || bitCountPerPix == 32) {
		return 1;
	}
	if (bitCountPerPix == 16 || bitCountPerPix == 8 || bitCountPerPix == 4) {
		return 0;
	}
	return -1;
}

int checkXBMDataCompression(BitmapInfo* bi) {
	if (bi->biCompressionType > 0 && bi->biCompressionType < 6) {
		/*BMP图像数据被压缩需要解压*/
		return 1;
	}
	if (bi->biCompressionType == 0) {
		/*未压缩状态*/
		return 0;
	}
	/*数据异常*/
	return -1;
}

int readXBMDataFromFile(BitmapFileHeader* bfh, BitmapInfo* bi, BitmapPalette* bp, uXBMInt32*** pixRGBDataHeaderPtr, std::fstream* fin) {
	fin->seekg(std::ios::beg);
	fin->read((char*)bfh, sizeof(BitmapFileHeader));
	fin->read((char*)(&bi->bInfoTagSize), sizeof(uXBMInt32));
	fin->read((char*)(&bi->biWidthPix), sizeof(BitmapInfo) - sizeof(uXBMInt32));
	if (!checkXBMDataValidity(bfh, bi, bp)) {
		/*读入的数据无效则返回0*/
		return 0;
	}
	if (!readXBMRGBDataFromFile(pixRGBDataHeaderPtr, bi, fin)) {
		return 0;
	}
	return 1;
}

int readXBMRGBDataFromFile(uXBMInt32*** pixRGBDataHeaderPtr, BitmapInfo* bi, std::fstream* fin) {
	uXBMInt32 rawWidthPix = bi->biWidthPix;
	uXBMInt32 rawHeightPix = (bi->biHeightPix < 0) ? -bi->biHeightPix : bi->biHeightPix;
	uXBMInt32 rawTotalPix = rawWidthPix * rawHeightPix;
	(*pixRGBDataHeaderPtr) = (uXBMInt32**) new uXBMInt32[rawTotalPix];
	if ((*pixRGBDataHeaderPtr) == NULL) {
		return 0;
	}
	memset((*pixRGBDataHeaderPtr), 0, rawTotalPix * sizeof(uXBMInt32));

	uXBMInt32 i;
	XBMByte c;
	uXBMInt32* pixRGBDataArrHead = (uXBMInt32*)(*pixRGBDataHeaderPtr);
	uXBMInt32* p;
	if (bi->biBitCountPerPix == 24) {
		if (bi->biHeightPix < 0) {
			p = pixRGBDataArrHead;
			for (i = 0; i < rawTotalPix; i++, p++) {
				fin->read((char*)p, 3);
			}
		}
		else {
			p = pixRGBDataArrHead + rawTotalPix - 1;
			for (i = 0; i < rawTotalPix; i++, p--) {
				fin->read((char*)p, 3);
			}
		}
	}
	else if (bi->biBitCountPerPix == 32) {
		if (bi->biHeightPix < 0) {
			p = pixRGBDataArrHead;
			for (i = 0; i < rawTotalPix; i++, p++) {
				fin->read((char*)p, 3);
				fin->read(&c, 1);
			}
		}
		else {
			p = pixRGBDataArrHead + rawTotalPix - 1;
			for (i = 0; i < rawTotalPix; i++, p--) {
				fin->read((char*)p, 3);
				fin->read(&c, 1);
			}
		}
	}
	return 1;
}

int saveXBMFile(const char* filePath) {
	return 0;
}
uXBMInt32 getFileSize(const char* filePath) {
	uXBMInt32 fLength;
	std::ifstream fin(filePath,std::ios::binary);
	if (!fin.is_open()) {
		return 0;
	}
	fin.seekg(0, std::ios::end);
	fLength = fin.tellg();
	fin.close();
	return fLength;
}