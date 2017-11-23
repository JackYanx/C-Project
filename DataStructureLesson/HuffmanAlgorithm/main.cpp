#include "commen.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

int main() {
	
	string s = "C:\\Users\\Asus\\Desktop\\5.bmp";

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