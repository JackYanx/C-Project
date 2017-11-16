#include "commen.h"
#include "HuffmanEncoder.h"

int main() {
	HuffmanEncoder mEncoder;
	mEncoder.build("待压缩的文件","压缩好的文件");
	mEncoder.encode();
	cin.get();
	return 0;
}