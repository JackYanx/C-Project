#include "commen.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

int main() {
	
	HuffmanEncoder mEncoder;
	mEncoder.build("D:\\0.txt","D:\\0-zipped.txt");
	mEncoder.encode();
	
	HuffmanDecoder mDecoder;
	mDecoder.build("D:\\0-zipped.txt", "D:\\0-zipped-unzipped.txt");
	mDecoder.decode();



	cin.get();
	return 0;
}