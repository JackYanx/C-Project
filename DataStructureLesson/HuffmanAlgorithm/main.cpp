#include "commen.h"
#include "HuffmanEncoder.h"

int main() {
	HuffmanEncoder mEncoder;
	mEncoder.build("D:\\111.txt","D:\\111-zipped.txt");
	mEncoder.encode();
	cin.get();
	return 0;
}