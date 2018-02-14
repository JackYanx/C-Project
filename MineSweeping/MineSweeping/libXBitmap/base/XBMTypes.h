#ifndef XBMTYPES_H
#define XBMTYPES_H

#pragma once
#pragma pack(push)
#pragma pack(2)

typedef char            XBMByte;
typedef unsigned char   uXBMByte;
typedef short           XBMInt16;
typedef unsigned short  uXBMInt16;
typedef long            XBMInt32;
typedef unsigned long   uXBMInt32;
#define XRGB(r, g, b) (uXBMInt32)(((uXBMByte)(r)|((uXBMInt16)((uXBMByte)(g))<<8))|(((uXBMInt32)(uXBMByte)(b))<<16))
typedef struct tag_BitmapFileHeader {
	uXBMInt16 bfType;
	uXBMInt32 bfSize;
	uXBMInt32 bfReserved;
	uXBMInt32 bfImageDataOffset;
} BitmapFileHeader;

typedef struct tag_BitmapInfo {
	uXBMInt32 bInfoTagSize;
	XBMInt32  biWidthPix;
	XBMInt32  biHeightPix;
	uXBMInt16 biPlanes;
	uXBMInt16 biBitCountPerPix;
	uXBMInt32 biCompressionType;
	uXBMInt32 biImageDataSize;
	XBMInt32  biXPelsPerMeter;
	XBMInt32  biYPelsPerMeter;
	uXBMInt32 biClrIdxUsed;
	uXBMInt32 biClrImportant;
} BitmapInfo;

typedef struct tag_BitmapRGBQUAD
{
	uXBMByte  rgbBlue;       //指定蓝色强度
	uXBMByte  rgbGreen;      //指定绿色强度
	uXBMByte  rgbRed;        //指定红色强度
	uXBMByte  rgbReserved;  //保留，设置为0
} BitmapPalette;

#pragma pack(pop)

#endif