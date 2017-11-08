#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <cstdio>
#include <fstream>
#include "XBMTypes.h"

int openXBMFile(const char* filePath, std::fstream* fin);
int checkXBMDataValidity(BitmapFileHeader* bfh, BitmapInfo* bi, BitmapPalette* bp);
int checkXBMBit(BitmapInfo* bi);
int checkXBMDataCompression(BitmapInfo* bi);
int readXBMDataFromFile(BitmapFileHeader* bfh, BitmapInfo* bi, BitmapPalette* bp, uXBMInt32*** pixRGBDataHeaderPtr, std::fstream* fin);
int readXBMRGBDataFromFile(uXBMInt32*** pixRGBDataHeaderPtr, BitmapInfo* bi, std::fstream* fin);
int saveXBMFile(const char* filePath);
uXBMInt32 getFileSize(const char* filePath);
#endif
