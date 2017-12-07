#include "commen.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

int main() {
	/*
	unsigned char ch = 0xFF;
	char* p = (char*)&ch;
	FILE* fp = fopen("C:\\Users\\Asus\\Desktop\\aaa.txt", "wb");
	if (fp == NULL) return -1;
	for (int i = 0; i < 65536; i++) {
		fwrite(p, 1, 1, fp);
		//ch++;
	}
	fclose(fp);
	*/
	
	string s = "D:\\5.bmp";

	string s1 = s + "-zipped";
	string s2 = s1 + "-unzipped";

	HuffmanEncoder mEncoder;
	mEncoder.build((char*)s.c_str(), (char*)s1.c_str());
	mEncoder.encode();
	
	HuffmanDecoder mDecoder;
	mDecoder.build((char*)s1.c_str(), (char*)s2.c_str());
	mDecoder.decode();
	
	return 0;
}