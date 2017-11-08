#ifndef BITMAPUTIL_H
#define BITMAPUTIL_H

#include "widget_base.h"

int drawBitmap(
	HDC hdc,
	const char* filePath,
	int x = 0,
	int y = 0,
	int bWidth = 0,
	int bHeight = 0,
	bool setCompression = 0
	);

#endif // !BITMAPUTIL_H
