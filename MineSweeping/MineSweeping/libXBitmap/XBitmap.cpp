#include <string.h>
#include "XBitmap.h"

XBitmap::XBitmap(const char* filePath) {
	onInitXBMObject();
	decodeXBMFile(filePath);
}

XBitmap::~XBitmap() {

}

int XBitmap::decodeXBMFile(const char* filePath) {
	if (filePath == NULL) {
		return 0;
	}
	if (mStatus == 1) {
		if (!strcmp(filePath, mAbsolutePath)) {
			/*判断打开的是否为相同文件*/
			return 1;
		}
		onRecycle();
	}
	if (!onInit()) {
		return 0;
	}
	if (!openXBMFile(filePath, &fImageStream)) {
		return 0;
	}
	if (!readXBMDataFromFile(mBitmapFileHeader, mBitmapInfo, mBitmapPalette, &pixRGBDataHeader, &fImageStream)) {
		onFailDecodeXBMFile();
		return 0;
	}
	pixRGBDataPtr = (uXBMInt32*)pixRGBDataHeader;
	fImageStream.seekg(std::ios::beg);
	strcpy_s(mAbsolutePath, strlen(filePath) + 1, filePath);
	mStatus = 1;
	return 1;
}
int XBitmap::onInitXBMObject() {
	mStatus = 0;
	mAbsolutePath = NULL;
	mBitmapFileHeader = NULL;
	mBitmapInfo = NULL;
	mBitmapPalette = NULL;
	pixRGBDataHeader = NULL;
	pixRGBDataPtr = NULL;
	return 0;
}
int XBitmap::onInit() {
	if (mStatus != 0) {
		return 0;
	}
	mAbsolutePath = new char[ABSOLUTE_PATH_MAXLENGTH];
	if (mAbsolutePath == NULL) {
		return 0;
	}
	
	mBitmapFileHeader = new BitmapFileHeader;
	if (mBitmapFileHeader == NULL) {
		delete[] mAbsolutePath;
		return 0;
	}
	
	mBitmapInfo = new BitmapInfo;
	if (mBitmapInfo == NULL) {
		delete[] mAbsolutePath;
		delete   mBitmapFileHeader;
		return 0;
	}
	
	mBitmapPalette = new BitmapPalette;
	if (mBitmapPalette == NULL) {
		delete[] mAbsolutePath;
		delete   mBitmapFileHeader;
		delete   mBitmapInfo;
		return 0;
	}

	memset(mAbsolutePath, 0, ABSOLUTE_PATH_MAXLENGTH);
	memset(mBitmapFileHeader, 0, sizeof(BitmapFileHeader));
	memset(mBitmapInfo, 0, sizeof(BitmapInfo));
	memset(mBitmapPalette, 0, sizeof(BitmapPalette));
	return 1;
}
int XBitmap::onRecycle() {
	if (mStatus != 1) {
		return 0;
	}
	delete[] (uXBMInt32*)pixRGBDataHeader;
	delete   mBitmapPalette;
	delete   mBitmapInfo;
	delete   mBitmapFileHeader;
	delete[] mAbsolutePath;
	pixRGBDataHeader = NULL;
	pixRGBDataPtr = NULL;
	mBitmapPalette = NULL;
	mBitmapInfo = NULL;
	mBitmapFileHeader = NULL;
	mAbsolutePath = NULL;
	fImageStream.close();
	mStatus = 0;
}

//uXBMInt32 curPixRGBVal;
uXBMByte r, g, b, *ptr;
uXBMInt32 XBitmap::getPixRGBValue() {
	ptr = (uXBMByte*)pixRGBDataPtr;
	r = *(ptr + 2);
	g = *(ptr + 1);
	b = *(ptr + 0);
	pixRGBDataPtr++;
	return XRGB(r, g, b);
}

uXBMInt32 XBitmap::seekPtr(uXBMInt32 offsite) {
	if (offsite > getWidthPix() * getHeightPix()) {
		return 0;
	}
	pixRGBDataPtr = (uXBMInt32*)pixRGBDataHeader + offsite;
	return 1;
}

int XBitmap::onFailDecodeXBMFile() {
	delete[] (uXBMInt32*)pixRGBDataHeader;
	delete   mBitmapPalette;
	delete   mBitmapInfo;
	delete[] mAbsolutePath;
	pixRGBDataHeader = NULL;
	pixRGBDataPtr = NULL;
	mBitmapPalette = NULL;
	mBitmapInfo = NULL;
	mBitmapFileHeader = NULL;
	mAbsolutePath = NULL;
	fImageStream.close();
	mStatus = 0;
	return 1;
}

uXBMInt32 XBitmap::getWidthPix() {
	return mBitmapInfo->biWidthPix;
}
uXBMInt32 XBitmap::getHeightPix() {
	return (mBitmapInfo->biHeightPix > 0) ? mBitmapInfo->biHeightPix : -mBitmapInfo->biHeightPix;
}