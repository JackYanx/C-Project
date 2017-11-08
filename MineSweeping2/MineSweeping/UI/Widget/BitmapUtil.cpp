#include "BitmapUtil.h"
#include "../../libXBitmap/XBitmap.h"

int drawBitmap(
	HDC hdc,
	const char* filePath,
	int x,
	int y,
	int bWidth,
	int bHeight,
	bool setCompression
)
{
	if (hdc == NULL || filePath == NULL) {
		return -1;
	}
	if (bWidth <= 0 || bHeight <= 0) {
		return -1;
	}
	static XBitmap* xBitmap = new XBitmap;
	xBitmap->decodeXBMFile(filePath);
	xBitmap->seekPtr(0);
	uXBMInt32 imgWidth = xBitmap->getWidthPix();
	uXBMInt32 imgHeight = xBitmap->getHeightPix();
	uXBMInt32 i, j;
	for (i = 0; i < imgHeight;i++) {
		for (j = imgWidth; j > 0;j--) {
			SetPixelV(hdc, j, i, 0x620CFF);
		}
	}
	
	return 0;
}
