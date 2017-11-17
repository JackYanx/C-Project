#include "commen.h"
#include "HuffmanEncoder.h"

int main() {
	HuffmanEncoder mEncoder;
	mEncoder.build("D:\\000.txt","D:\\000-zipped.txt");
	mEncoder.encode();
	cin.get();
	return 0;
}