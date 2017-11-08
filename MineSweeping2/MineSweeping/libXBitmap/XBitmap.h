#ifndef XBITMAP_H
#define XBITMAP_H

#include "base\XBMTypes.h"
#include "base\FileUtil.h"

#define ABSOLUTE_PATH_MAXLENGTH 256

class XBitmap {
protected:
	XBMInt32              mStatus;
	char*                 mAbsolutePath;
	BitmapFileHeader*     mBitmapFileHeader;
	BitmapInfo*           mBitmapInfo;
	BitmapPalette*        mBitmapPalette;
	uXBMInt32**           pixRGBDataHeader;
	uXBMInt32*            pixRGBDataPtr;
	std::fstream          fImageStream;
	int onInitXBMObject();
	int onInit();
	int onFailDecodeXBMFile();
public:
	XBitmap(const char* filePath = NULL);
	int decodeXBMFile(const char* filePath = NULL);
	int onRecycle();
	uXBMInt32 getPixRGBValue();
	uXBMInt32 seekPtr(uXBMInt32 offsite);
	uXBMInt32 getWidthPix();
	uXBMInt32 getHeightPix();
	~XBitmap();

};

#endif